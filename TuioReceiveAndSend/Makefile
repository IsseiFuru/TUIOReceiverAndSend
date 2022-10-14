PLATFORM=$(shell uname)
ENDIANESS=OSC_HOST_LITTLE_ENDIAN

LD_FLAGS = -lGL -lGLU -lglut

RECEIVE_AND_SEND = ReceiveAndSend
TUIO_STATIC = libTUIO.a
TUIO_SHARED = libTUIO.so

INCLUDES = -I./TUIO -I./oscpack
CXXFLAGS = $(INCLUDES) -D$(ENDIANESS)
SHARED_OPTIONS = -shared -Wl,-soname,$(TUIO_SHARED)

ifeq ($(PLATFORM), Darwin)
	TARGET = -mmacosx-version-min=10.9
	CXXFLAGS += $(TARGET)
	TUIO_SHARED = libTUIO.dylib
	SHARED_OPTIONS = -dynamiclib -Wl,-dylib_install_name,$(TUIO_SHARED)
endif

%.o: %.cpp
	@echo [CXX] $@
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

RECEIVE_AND_SEND_SOURCES = ReceiveAndSend.cpp
RECEIVE_AND_SEND_OBJECTS = ReceiveAndSend.o

COMMON_TUIO_SOURCES = ./TUIO/TuioTime.cpp ./TUIO/TuioPoint.cpp ./TUIO/TuioContainer.cpp ./TUIO/TuioObject.cpp ./TUIO/TuioCursor.cpp ./TUIO/TuioBlob.cpp ./TUIO/TuioDispatcher.cpp ./TUIO/TuioManager.cpp  ./TUIO/OneEuroFilter.cpp
SERVER_TUIO_SOURCES = ./TUIO/TuioServer.cpp ./TUIO/UdpSender.cpp ./TUIO/TcpSender.cpp ./TUIO/WebSockSender.cpp ./TUIO/FlashSender.cpp
CLIENT_TUIO_SOURCES = ./TUIO/TuioClient.cpp ./TUIO/OscReceiver.cpp ./TUIO/UdpReceiver.cpp ./TUIO/TcpReceiver.cpp
OSC_SOURCES = ./oscpack/osc/OscTypes.cpp ./oscpack/osc/OscOutboundPacketStream.cpp ./oscpack/osc/OscReceivedElements.cpp ./oscpack/osc/OscPrintReceivedElements.cpp ./oscpack/ip/posix/NetworkingUtils.cpp ./oscpack/ip/posix/UdpSocket.cpp

COMMON_TUIO_OBJECTS = $(COMMON_TUIO_SOURCES:.cpp=.o)
SERVER_TUIO_OBJECTS = $(SERVER_TUIO_SOURCES:.cpp=.o)
CLIENT_TUIO_OBJECTS = $(CLIENT_TUIO_SOURCES:.cpp=.o)
OSC_OBJECTS = $(OSC_SOURCES:.cpp=.o)

all: $(RECEIVE_AND_SEND) $(TUIO_STATIC) $(TUIO_SHARED)

$(TUIO_STATIC):	$(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS)
	@echo [LD] $(TUIO_STATIC)
	@ ar rcs $@ $(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS)

$(TUIO_SHARED): $(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS)
	@echo [LD] $(TUIO_SHARED)
	@ $(CXX) -o $@ $+ -lpthread $(SHARED_OPTIONS)

$(RECEIVE_AND_SEND): $(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(OSC_OBJECTS) $(RECEIVE_AND_SEND_OBJECTS)
	@echo [LD] $(RECEIVE_AND_SEND)
	@ $(CXX) -o $@ $+ -lpthread

clean:
	@echo [CLEAN] $(RECEIVE_AND_SEND) $(TUIO_STATIC) $(TUIO_SHARED)
	@ rm -f $(RECEIVE_AND_SEND) $(TUIO_STATIC) $(TUIO_SHARED)
	@ rm -f $(COMMON_TUIO_OBJECTS) $(CLIENT_TUIO_OBJECTS) $(SERVER_TUIO_OBJECTS) $(OSC_OBJECTS) $(DUMP_OBJECTS) $(DEMO_OBJECTS) $(SIMULATOR_OBJECTS)
