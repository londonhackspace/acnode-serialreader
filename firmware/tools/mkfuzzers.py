# This script outputs test cases for AFL (https://lcamtuf.coredump.cx/afl/)
# for use with commsfuzzharness

i = 0

def writesample(data):
	global i
	with open("fuzz-inputs/" + str(i) + ".dat", "wb") as f:
		f.write(data)
	i += 1

writesample(bytearray([0xff, 0xdd,
        0x82, 0x12,
        0x01,
        0x07, ord('c'), ord('o'), ord('n'), ord('t'), ord('e'), ord('x'), ord('t'),
        0x07, ord('m'), ord('e'), ord('s'), ord('s'), ord('a'), ord('g'), ord('e'),
        0x73]))


writesample(bytearray( [0xff, 0xdd,
        0x82, 0x35,
        0x03,
        0x0f, ord('s'), ord('r'), ord('c'), ord('/'), ord('p'), ord('n'), ord('5'), ord('3'), ord('2'), ord('.'), ord('c'), ord(':'), ord('1'), ord('1'), ord('2'),
        0x22, ord('I'), ord('2'), ord('C'), ord(' '), ord('S'), ord('e'), ord('n'), ord('d'), ord('i'), ord('n'), ord('g'), ord(' '), ord(' '), ord('0'), ord(' '), ord('0'), ord(' '), ord('f'), ord('f'), ord(' '), ord('2'), ord(' '), ord('f'), ord('e'), ord(' '),ord('d'), ord('4'), ord(' '), ord('2'), ord(' '), ord('2'), ord('a'), ord(' '), ord('0'),
        0x2b,
        0xfd, 0x02,
        0xff, 0xdd,
        0x82, 0x12,
        0x02,
        0x07, ord('c'), ord('o'), ord('n'), ord('t'), ord('e'), ord('x'), ord('t'),
        0x07, ord('m'), ord('e'), ord('s'), ord('s'), ord('a'), ord('g'), ord('e'),
        0x72,
        0xfd, 0x02,
        0xff, 0xdd,
        0x82, 0x35,
        0x03,
        0x0f, ord('s'), ord('r'), ord('c'), ord('/'), ord('p'), ord('n'), ord('5'), ord('3'), ord('2'), ord('.'), ord('c'), ord(':'), ord('1'), ord('1'), ord('2'),
        0x22, ord('I'), ord('2'), ord('C'), ord(' '), ord('S'), ord('e'), ord('n'), ord('d'), ord('i'), ord('n'), ord('g'), ord(' '), ord(' '), ord('0'), ord(' '), ord('0'), ord(' '), ord('f'), ord('f'), ord(' '), ord('2'), ord(' '), ord('f'), ord('e'), ord(' '),ord('d'), ord('4'), ord(' '), ord('2'), ord(' '), ord('2'), ord('a'), ord(' '), ord('0'),
        0x2b,
        0xfd, 0x03,
        0xff, 0xdd,
        0x82, 0x35,
        0x03,
        0x0f, ord('s'), ord('r'), ord('c'), ord('/'), ord('p'), ord('n'), ord('5'), ord('3'), ord('2'), ord('.'), ord('c'), ord(':'), ord('1'), ord('1'), ord('2'),
        0x22, ord('I'), ord('2'), ord('C'), ord(' '), ord('S'), ord('e'), ord('n'), ord('d'), ord('i'), ord('n'), ord('g'), ord(' '), ord(' '), ord('0'), ord(' '), ord('0'), ord(' '), ord('f'), ord('f'), ord(' '), ord('2'), ord(' '), ord('f'), ord('e'), ord(' '),ord('d'), ord('4'), ord(' '), ord('2'), ord(' '), ord('2'), ord('a'), ord(' '), ord('0'),
        0x2b,
        0xfd, 0x02,
        ]))