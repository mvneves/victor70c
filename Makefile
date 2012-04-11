
HIDAPI_PATH = ../hidapi
INSTALL_DIR = /usr

build:
	gcc -Wall -o victor70c victor70c.c -lusb-1.0 -lpthread -I$(HIDAPI_PATH)/hidapi/ -L$(HIDAPI_PATH)/linux/ -lhidapi-hidraw

install:
	cp -a $(HIDAPI_PATH)/hidapi/hidapi.h $(INSTALL_DIR)/include
	cp -a $(HIDAPI_PATH)/linux/libhidapi-hidraw.so $(INSTALL_DIR)/lib
	ln -s libhidapi-hidraw.so $(INSTALL_DIR)/lib/libhidapi-hidraw.so.0
	cp -a victor70c $(INSTALL_DIR)/bin

