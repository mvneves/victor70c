#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <hidapi.h>
#include <getopt.h>

#define VICTOR70C_VENDOR_ID 0x1244
#define VICTOR70C_PRODUCT_ID 0xd237

#define VICTOR70C_DIGIT0_0 0x81
#define VICTOR70C_DIGIT0_1 0x01
#define VICTOR70C_DIGIT0_2 0xC1
#define VICTOR70C_DIGIT0_3 0x41
#define VICTOR70C_DIGIT0_4 0xA1
#define VICTOR70C_DIGIT0_5 0x21
#define VICTOR70C_DIGIT0_6 0xE1
#define VICTOR70C_DIGIT0_7 0x61
#define VICTOR70C_DIGIT0_8 0x91
#define VICTOR70C_DIGIT0_9 0x11

#define VICTOR70C_DIGIT1_0 0x6F
#define VICTOR70C_DIGIT1_1 0xEF
#define VICTOR70C_DIGIT1_2 0xAF
#define VICTOR70C_DIGIT1_3 0x2F
#define VICTOR70C_DIGIT1_4 0x8F
#define VICTOR70C_DIGIT1_5 0x0F
#define VICTOR70C_DIGIT1_6 0xCF
#define VICTOR70C_DIGIT1_7 0x4F
#define VICTOR70C_DIGIT1_8 0x7F
#define VICTOR70C_DIGIT1_9 0xFF

#define VICTOR70C_DIGIT2_0 0x71
#define VICTOR70C_DIGIT2_1 0xF1
#define VICTOR70C_DIGIT2_2 0xB1
#define VICTOR70C_DIGIT2_3 0x31
#define VICTOR70C_DIGIT2_4 0x91
#define VICTOR70C_DIGIT2_5 0x11
#define VICTOR70C_DIGIT2_6 0xD1
#define VICTOR70C_DIGIT2_7 0x51
#define VICTOR70C_DIGIT2_8 0x81
#define VICTOR70C_DIGIT2_9 0x01

#define VICTOR70C_DIGIT3_0 0x77
#define VICTOR70C_DIGIT3_1 0xF7
#define VICTOR70C_DIGIT3_2 0xB7
#define VICTOR70C_DIGIT3_3 0x37
#define VICTOR70C_DIGIT3_4 0x97
/*
#define VICTOR70C_DIGIT3_5	0x00
#define VICTOR70C_DIGIT3_6	0x00
#define VICTOR70C_DIGIT3_7	0x00
#define VICTOR70C_DIGIT3_8	0x00
#define VICTOR70C_DIGIT3_9	0x00
*/

/* Flag set by ‘--verbose’. */
static int verbose_flag = 0;

void victor70c_decode(unsigned char *buf, char *str)
{
	int m, V, A, minus, acdc, dc, decimal;
	int digit[4] = {0, 0, 0, 0};

	switch (buf[6])
	{
	case VICTOR70C_DIGIT0_0:
		digit[0] = 0;
		break;
	case VICTOR70C_DIGIT0_1:
		digit[0] = 1;
		break;
	case VICTOR70C_DIGIT0_2:
		digit[0] = 2;
		break;
	case VICTOR70C_DIGIT0_3:
		digit[0] = 3;
		break;
	case VICTOR70C_DIGIT0_4:
		digit[0] = 4;
		break;
	case VICTOR70C_DIGIT0_5:
		digit[0] = 5;
		break;
	case VICTOR70C_DIGIT0_6:
		digit[0] = 6;
		break;
	case VICTOR70C_DIGIT0_7:
		digit[0] = 7;
		break;
	case VICTOR70C_DIGIT0_8:
		digit[0] = 8;
		break;
	case VICTOR70C_DIGIT0_9:
		digit[0] = 9;
		break;
	default:
		printf("Invalid digit0 = 0x%x\n", buf[6]);
	}

	switch (buf[9])
	{
	case VICTOR70C_DIGIT1_0:
		digit[1] = 0;
		break;
	case VICTOR70C_DIGIT1_1:
		digit[1] = 1;
		break;
	case VICTOR70C_DIGIT1_2:
		digit[1] = 2;
		break;
	case VICTOR70C_DIGIT1_3:
		digit[1] = 3;
		break;
	case VICTOR70C_DIGIT1_4:
		digit[1] = 4;
		break;
	case VICTOR70C_DIGIT1_5:
		digit[1] = 5;
		break;
	case VICTOR70C_DIGIT1_6:
		digit[1] = 6;
		break;
	case VICTOR70C_DIGIT1_7:
		digit[1] = 7;
		break;
	case VICTOR70C_DIGIT1_8:
		digit[1] = 8;
		break;
	case VICTOR70C_DIGIT1_9:
		digit[1] = 9;
		break;
	default:
		printf("Invalid digit1 = 0x%x\n", buf[9]);
	}

	switch (buf[3])
	{
	case VICTOR70C_DIGIT2_0:
		digit[2] = 0;
		break;
	case VICTOR70C_DIGIT2_1:
		digit[2] = 1;
		break;
	case VICTOR70C_DIGIT2_2:
		digit[2] = 2;
		break;
	case VICTOR70C_DIGIT2_3:
		digit[2] = 3;
		break;
	case VICTOR70C_DIGIT2_4:
		digit[2] = 4;
		break;
	case VICTOR70C_DIGIT2_5:
		digit[2] = 5;
		break;
	case VICTOR70C_DIGIT2_6:
		digit[2] = 6;
		break;
	case VICTOR70C_DIGIT2_7:
		digit[2] = 7;
		break;
	case VICTOR70C_DIGIT2_8:
		digit[2] = 8;
		break;
	case VICTOR70C_DIGIT2_9:
		digit[2] = 9;
		break;
	default:
		printf("Invalid digit2 = 0x%x\n", buf[3]);
	}

	switch (buf[10])
	{
	case VICTOR70C_DIGIT3_0:
		digit[3] = 0;
		break;
	case VICTOR70C_DIGIT3_1:
		digit[3] = 1;
		break;
	case VICTOR70C_DIGIT3_2:
		digit[3] = 2;
		break;
	case VICTOR70C_DIGIT3_3:
		digit[3] = 3;
		break;
	case VICTOR70C_DIGIT3_4:
		digit[3] = 4;
		break;
	/*
	case VICTOR70C_DIGIT3_5:
	case VICTOR70C_DIGIT3_6:
	case VICTOR70C_DIGIT3_7:
	case VICTOR70C_DIGIT3_8:
	case VICTOR70C_DIGIT3_9:
		break;
*/
	default:
		printf("Invalid digit3 = 0x%x\n", buf[10]);
	}

	acdc = (buf[1] & 0x60) >> 5;
	if (acdc == 0x02)
	{
		dc = 0;
	}
	else if (acdc == 0x01)
	{
		dc = 1;
	}

	decimal = (buf[5] & 0xE0) >> 5;
	if (decimal == 0x00)
	{
		decimal = 2;
	}
	else if (decimal == 0x06)
	{
		decimal = 1;
	}
	else if (decimal == 0x05)
	{
		decimal = 0;
	}

	minus = buf[4] & 0x01;
	m = (buf[12] & 0x02) >> 1;
	V = (buf[4] & 0x80) >> 7;
	A = buf[8] & 0x01;

#if 0
	sprintf(str, "%s%d%s%d%s%d%s%d %s%s%s %s", 
		minus ? "-" : "", 
		digit[3], 
		decimal == 2 ? "." : "", 
		digit[2],
		decimal == 1 ? "." : "",
		digit[1],
		decimal == 0 ? "." : "",
		digit[0],
		m ? "m" : "",
		V ? "V" : "",
		A ? "A" : "",
		dc ? "DC" : "AC");
#else
	sprintf(str, "%s%d%s%d%s%d%s%d",
			minus ? "-" : "",
			digit[3],
			decimal == 2 ? "." : "",
			digit[2],
			decimal == 1 ? "." : "",
			digit[1],
			decimal == 0 ? "." : "",
			digit[0]);
#endif

	return;
}

double get_seconds()
{
	struct timeval tv;
	double time;

	gettimeofday(&tv, NULL);
	time = (double)tv.tv_sec + (double)tv.tv_usec / 1000 / 1000;

	return time;
}

int check_elapsed_time(int now, int interval)
{
	static int last = 0;

	if (interval == 0)
		return 1;

	if ((now - last) >= interval)
	{
		last = now;
		return 1;
	}

	return 0;
}

void print_help()
{
	printf("Usage: victor70c [options] duration\n");
	printf("Options:\n");
	printf("   -i --interval          interval in seconds between each read\n");
	printf("   -v --verbose           turn on verbose output\n");
	printf("   -h --help              print this help message\n");
}

int main(int argc, char *argv[])
{
	int ret;
	unsigned char buf[256];
	char str[256];
	hid_device *handle;
	double now;
	double start;
	double duration = 0;
	double interval = 0;
	int c;
	int option_index = 0;

	while (1)
	{
		static struct option long_options[] = {
			{"help", no_argument, 0, 'h'},
			{"verbose", no_argument, 0, 'v'},
			{"interval", required_argument, 0, 'i'},
			{0, 0, 0, 0}};

		c = getopt_long(argc, argv, "hvi:", long_options,
						&option_index);

		if (c == -1)
			break;

		switch (c)
		{
		case 'i':
			interval = (double)atoi(optarg);
			break;

		case 'v':
			verbose_flag = 1;
			break;

		case '?':
		case 'h':
		default:
			print_help();
		}
	}

	if (optind >= argc)
	{
		print_help();
		exit(1);
	}

	duration = (double)atol(argv[optind]);

	start = get_seconds();

	handle = hid_open(VICTOR70C_VENDOR_ID, VICTOR70C_PRODUCT_ID, NULL);
	if (!handle)
	{
		printf("Cannot found victor70C.\n");
		exit(1);
	}

	do
	{
		ret = hid_read(handle, buf, sizeof(buf));
		if (ret <= 0 || buf[0] == 0)
			continue;

		now = get_seconds();
		if (check_elapsed_time((int)now, interval) == 0)
			continue;

		victor70c_decode(buf, str);
		printf("%lf %s\n", now, str);
		fflush(stdout);
	} while ((now - start) < duration);

	hid_close(handle);
	hid_exit();

	return 0;
}
