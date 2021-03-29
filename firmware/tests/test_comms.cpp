#include "../src/commsprotocol.h"
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>

static std::queue<std::vector<unsigned char>> rxqueue;
static std::queue<std::vector<unsigned char>> txqueue;

static bool readerVersionQueried = false;
static bool logReceived = false;

static uint8_t led_r = 0;
static uint8_t led_g = 0;
static uint8_t led_b = 0;

extern "C" void comms_query_reader_version_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    readerVersionQueried = true;
}

extern "C" void comms_log_message_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    logReceived = true;
}

extern "C" void comms_set_led_handler(comms_context_t* comms, unsigned char code, unsigned char* payload, size_t payloadLength)
{
    led_r = payload[0];
    led_g = payload[1];
    led_b = payload[2];
}

static void test_reset()
{
    rxqueue = std::queue<std::vector<unsigned char>>();
    txqueue = std::queue<std::vector<unsigned char>>();
    readerVersionQueried = false;
}

static unsigned int rxfunc(unsigned char* data,unsigned int maxsize)
{
    if(rxqueue.empty())
    {
        return 0;
    }
    std::vector<unsigned char> &buffer = rxqueue.front();
    if(maxsize > buffer.size())
    {
        maxsize = buffer.size();
    }

    memcpy(data, buffer.data(), maxsize);
    rxqueue.pop();
    return maxsize;
}

static void txfunc(const unsigned char* data,unsigned int size)
{
    std::vector<unsigned char> buffer(size, 0);
    memcpy(buffer.data(), data, size);
    txqueue.push(std::move(buffer));
}

#define STRINGIFY_(S) #S
#define STRINGIFY(S) STRINGIFY_(S)
#define ADD_TEST(func) test_reset(); if(!func()) { std::cerr << "[Fail] " STRINGIFY(func) << std::endl; retval = 1; } else std::cerr << "[Pass] " STRINGIFY(func) << std::endl
#define TEST_PASS() return true
#define TEST_FAIL() return false
#define TEST_ASSERT(VAL) if(!(VAL)) {std::cerr << "Assertion Fail: "  STRINGIFY((VAL)) << std::endl; return false; } if(0)

static bool test_log_send_error()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_log(&victim, LOG_LEVEL_WARN, "context", "message", 7);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x82, 0x12,
        0x01,
        0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
        0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
        0x73
    };

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_log_send_info()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_log(&victim, LOG_LEVEL_INFO, "context", "message", 7);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x82, 0x12,
        0x02,
        0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
        0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
        0x72
    };

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_log_send_error_zero()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_logz(&victim, LOG_LEVEL_WARN, "context", "message");

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x82, 0x12,
        0x01,
        0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
        0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
        0x73
    };

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

#ifdef __AVR__
static bool test_log_send_error_flash()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_log_flash(&victim, LOG_LEVEL_WARN, "context", "message", 7);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x82, 0x12,
        0x01,
        0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
        0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
        0x73
    };

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_log_send_info_flash()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_log_flash(&victim, LOG_LEVEL_INFO, "context", "message", 7);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x82, 0x12,
        0x02,
        0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
        0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
        0x72
    };

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_log_send_error_zero_flash()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_logz_flash(&victim, LOG_LEVEL_WARN, "context", "message");

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x82, 0x12,
        0x01,
        0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
        0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
        0x73
    };

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

#endif

// taken from a real log message example
// when multiple messages were sent, the checksum was including the previous checksum  and hence wrong
static bool test_sample_log_message()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_logz(&victim, LOG_LEVEL_DEBUG, "src/pn532.c:112", "I2C Sending  0 0 ff 2 fe d4 2 2a 0");

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x82, 0x35,
        0x03,
        0x0f, 's', 'r', 'c', '/', 'p', 'n', '5', '3', '2', '.', 'c', ':', '1', '1', '2',
        0x22, 'I', '2', 'C', ' ', 'S', 'e', 'n', 'd', 'i', 'n', 'g', ' ', ' ', '0', ' ', '0', ' ', 'f', 'f', ' ', '2', ' ', 'f', 'e', ' ', 'd', '4', ' ', '2', ' ', '2', 'a', ' ', '0',
        0x2b
    };

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    // now try again
    comms_send_logz(&victim, LOG_LEVEL_DEBUG, "src/pn532.c:112", "I2C Sending  0 0 ff 2 fe d4 2 2a 0");

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_send_reader_version_response()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x81, 34,

        0x14, 0x42,

        15, '2', '0', '2', '0', '-', '8', '-', '2', '5', ' ', '1', '5', ':', '2', '7',
        14, 'h', 'a', 's', 'h', ' ', 'g', 'o', 'e','s', ' ', 'h', 'e', 'r', 'e',

        0xce
    };

    comms_send_reader_version_response(&victim, 0x14, 0x42, "2020-8-25 15:27", "hash goes here");

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    // trigger an ACK
    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_send_temperature_query()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x03, 1,

        0xfc
    };

    comms_send_temperature_query(&victim);

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_send_temperature_response()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x83, 3,

        0x43, 0x41,

        0xf6
    };

    comms_send_temperature_response(&victim, 0x43, 0x41);

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_log_send_repeated()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    for(int i = 0; i < 1000; ++i)
    {
        comms_send_log(&victim, LOG_LEVEL_INFO, "context", "message", 7);

        std::vector<unsigned char> refmessage = {
            0xff, 0xdd,
            0x82, 0x12,
            0x02,
            0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
            0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
            0x72
        };

        TEST_ASSERT(txqueue.size() == 1);
        TEST_ASSERT(txqueue.front() == refmessage);
        txqueue.pop();

        // trigger an ACK
        rxqueue.push({ 0xfd, 0x02 });
        comms_poll(&victim);

        // Check the ACK has been collected
        TEST_ASSERT(rxqueue.empty());

        // check the comms handler is idle
        TEST_ASSERT(victim.state == 0);
    }

    TEST_PASS();
}

static bool test_send_bootloader_status_query()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x20, 1,

        0xdf
    };

    comms_send_bootloader_status_query(&victim);

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_send_bootloader_status_response()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0xa0, 2,
        0x00,

        0x5e
    };

    comms_send_bootloader_status_response(&victim, BOOTLOADER_STATUS_NOT_BOOTLOADER);

    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == refmessage);
    txqueue.pop();

    rxqueue.push({ 0xfd, 0x02 });
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

// There's little point testing receiving all messages,
// so we use this one as a representative sample
// Well, we probably should test them all,
// but that's tedious and I don't think it's worth it
static bool test_receive_reader_version_query()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    std::vector<unsigned char> refmessage = {
        0xff, 0xdd,
        0x01, 1,

        0xfe
    };

    std::vector<unsigned char> ackMessage = {
        0xfd, 0x02
    };

    rxqueue.push(refmessage);

    TEST_ASSERT(!readerVersionQueried);
    comms_poll(&victim);

    // make sure we got an ack to that
    TEST_ASSERT(txqueue.size() == 1);
    TEST_ASSERT(txqueue.front() == ackMessage);
    txqueue.pop();

    TEST_ASSERT(readerVersionQueried);

    // make sure the buffer is now empty
    TEST_ASSERT(victim.buffer_level == 0);

    TEST_PASS();
}

// regression test for bug found
static bool test_send_junk_before_ack()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    comms_send_log(&victim, LOG_LEVEL_INFO, "context", "message", 7);
    // we don't actually care much about the message in this test
    txqueue.pop();

    std::vector<unsigned char> manyZeros(48, 0x00);
    std::vector<unsigned char> paddedAck(60, 0x00);

    // append a buffer of junk
    rxqueue.push(manyZeros);

    paddedAck[58] = 0xfd;
    paddedAck[59] = 0x02;

    rxqueue.push(paddedAck);
    comms_poll(&victim);
    comms_poll(&victim);

    // Check the ACK has been collected
    TEST_ASSERT(rxqueue.empty());

    // check the comms handler is idle
    TEST_ASSERT(victim.state == 0);

    TEST_PASS();
}

static bool test_receive_log()
{
    std::vector<unsigned char> refmessage = {
            0x55, 0x23,
            0xff, 0xdd,
            0x82, 0x12,
            0x02,
            0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
            0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
            0x72
        };

    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);
    rxqueue.push(refmessage);
    logReceived = false;

    comms_poll(&victim);

    TEST_ASSERT(rxqueue.size() == 0);

    TEST_ASSERT(logReceived);

    // make sure it consumed all of it
    TEST_ASSERT(victim.buffer_level == 0);

    TEST_PASS();
}

static bool test_receive_log_with_extra_partial_message()
{
    // a message, some junk, then two bytes of the next message
    // we expect it to deal with everything except that last partial message
    std::vector<unsigned char> refmessage = {
            0xff, 0xdd,
            0x82, 0x12,
            0x02,
            0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
            0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
            0x72,

            0x42, 0x42, 0x21,

            0xff, 0xdd
        };

    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);
    rxqueue.push(refmessage);
    logReceived = false;

    comms_poll(&victim);

    TEST_ASSERT(rxqueue.size() == 0);

    TEST_ASSERT(logReceived);

    // make sure it consumed all of it, except for two remaining bytes
    TEST_ASSERT(victim.buffer_level == 2);

    TEST_PASS();
}

static bool test_receive_many_logs()
{
    std::vector<unsigned char> refmessage = {
            0x55, 0x23,
            0xff, 0xdd,
            0x82, 0x12,
            0x02,
            0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
            0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
            0x72
        };

    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);
    for(int i = 0; i < 20; ++i)
    {
        rxqueue.push(refmessage);
    }
    logReceived = false;

    while(rxqueue.size())
    {
        comms_poll(&victim);
    }

    TEST_ASSERT(logReceived);

    // make sure it consumed all of it
    TEST_ASSERT(victim.buffer_level == 0);

    TEST_PASS();
}

static bool test_receive_many_logs_fragmented()
{
    std::vector<unsigned char> refmessage_a = {
            0x55, 0x23,
            0xff, 0xdd,
        };
   std::vector<unsigned char> refmessage_b = {
            0x82, 0x12,
            0x02,
        };
    std::vector<unsigned char> refmessage_c = {
            0x07, 'c', 'o', 'n', 't', 'e', 'x', 't',
            0x07, 'm', 'e', 's', 's', 'a', 'g', 'e',
            0x72
        };

    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);
    for(int i = 0; i < 20; ++i)
    {
        rxqueue.push(refmessage_a);
        rxqueue.push(refmessage_b);
        rxqueue.push(refmessage_c);
    }
    logReceived = false;

    while(rxqueue.size())
    {
        comms_poll(&victim);
    }

    TEST_ASSERT(logReceived);

    // make sure it consumed all of it
    TEST_ASSERT(victim.buffer_level == 0);

    TEST_PASS();
}

bool test_light_set_in_middle_of_logs()
{
    comms_context_t victim;
    comms_init(&victim);
    comms_set_handlers(&victim, txfunc, rxfunc);

    std::vector<unsigned char> lightmessage = {
            0xff, 0xdd,
            0x05, 0x04,
            0xff, 0x37, 0x00,
            0xc1,
        };

        comms_send_logz(&victim, 1, "context", "Testing a log message");
        comms_poll(&victim);
        // remove any transmitted bytes since we don't actually care about them
        while(txqueue.size()) txqueue.pop();

        // send lights set message
        rxqueue.push(lightmessage);
        comms_poll(&victim);

        // there should be an ack here
        TEST_ASSERT(txqueue.size() == 1);
        TEST_ASSERT(txqueue.front() == std::vector<unsigned char>({0xfd, 0x02}));

        // lights should be set
        TEST_ASSERT(led_r == 0xff);
        TEST_ASSERT(led_g == 0x37);
        TEST_ASSERT(led_b == 0x00);

        TEST_PASS();
}

int main(int argc, char** argv)
{
    int retval = 0;
    test_reset();

    ADD_TEST(test_log_send_error);
    ADD_TEST(test_log_send_info);
    ADD_TEST(test_log_send_error_zero);

    // This is intended not to run on AVR, but to test AVR code using stubs for the _P functions
#ifdef __AVR__
    // Testing the flash versions on the host isn't perfect but it at least proves they exist
    ADD_TEST(test_log_send_error_flash);
    ADD_TEST(test_log_send_info_flash);
    ADD_TEST(test_log_send_error_zero_flash);
#endif

    ADD_TEST(test_sample_log_message);
    ADD_TEST(test_send_reader_version_response);

    ADD_TEST(test_send_temperature_query);
    ADD_TEST(test_send_temperature_response);
    ADD_TEST(test_receive_reader_version_query);

    ADD_TEST(test_log_send_repeated);

    ADD_TEST(test_send_bootloader_status_query);
    ADD_TEST(test_send_bootloader_status_response);

    ADD_TEST(test_send_junk_before_ack);

    ADD_TEST(test_receive_log);
    ADD_TEST(test_receive_log_with_extra_partial_message);
    ADD_TEST(test_receive_many_logs);
    ADD_TEST(test_receive_many_logs_fragmented);

    ADD_TEST(test_light_set_in_middle_of_logs);

    return retval;
}