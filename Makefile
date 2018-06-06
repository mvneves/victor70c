HIDAPI_PATH = ../hidapi
INSTALL_DIR = /usr

build:
	gcc -Wall -o victor70c victor70c.c -lusb-1.0 -lpthread -I$(HIDAPI_PATH)/hidapi/ -L$(HIDAPI_PATH)/linux/ -lhidapi-hidraw

install:
	cp  /usr/local/lib/libhidapi-hidraw.so.0  $(INSTALL_DIR)/lib
	cp -a victor70c $(INSTALL_DIR)/bin
