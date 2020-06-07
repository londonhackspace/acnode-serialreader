#include "../src/commsprotocol.h"
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>

static std::queue<std::vector<unsigned char>> rxqueue;
static std::queue<std::vector<unsigned char>> txqueue;


static void test_reset()
{
	rxqueue = std::queue<std::vector<unsigned char>>();
	txqueue = std::queue<std::vector<unsigned char>>();
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
#define ADD_TEST(func) if(!func()) { std::cerr << "[Fail] " STRINGIFY(func) << std::endl; retval = 1; } else std::cerr << "[Pass] " STRINGIFY(func) << std::endl
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

	return retval;
}