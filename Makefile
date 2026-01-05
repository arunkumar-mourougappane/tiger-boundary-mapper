PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CC=gcc
CXX=g++

CFLAGS += -g -Wall -Werror
CXXFLAGS += -g -Wall -Werror

CFLAGS += -g -lpq

CXXFLAGS += -g -lpq

INC_DIRS += \
	-I./include \
	-I/usr/include/postgresql

LIB_DIRS += \
	-L./build/lib \
	
BUILDDIR = build
BUILDDIR_APP = $(BUILDDIR)/app
BUILDDIR_LIB = $(BUILDDIR)/lib


COMPILE.cc = $(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c
LINKXX = $(CXX) $(LDFLAGS) $(LIB_DIRS)


TREE_DIRS = \
	$(BUILDDIR)/lib/psql_wrapper \
	$(BUILDDIR)/lib/tiger_shape_mapper \
	$(BUILDDIR)/app/shape_data_app

LIBS += \
	$(BUILDDIR_LIB)/libpsql_wrapper.a \
	$(BUILDDIR_LIB)/libtiger_shape_mapper.a

APPS = \
	$(BUILDDIR_APP)/shape_data_app/shape_data_app

TIGER_SHAPE_PARSER_OBJS = \
	$(BUILDDIR_LIB)/tiger_shape_mapper/rtc_bnd_wrapper.o \
	$(BUILDDIR_LIB)/tiger_shape_mapper/tiger_shape_file_parser.o

all: tree libs apps

tree:
	@mkdir -p $(TREE_DIRS)
	
libs: $(LIBS)

apps:	$(APPS)

clean:
	rm -fr $(BUILDDIR) $(OUTPUT_DIR)

$(BUILDDIR_LIB)/psql_wrapper/%.o: $(PROJECT_ROOT)/src/lib/psql_wrapper/%.cpp
	$(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c -std=c++20 -o$@ $<


$(BUILDDIR_LIB)/tiger_shape_mapper/%.o: $(PROJECT_ROOT)/src/lib/tiger_shape_mapper/%.cpp
	$(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c -std=c++20 -o$@ $<

$(BUILDDIR)/app/shape_data_app/%.o: $(PROJECT_ROOT)/src/app/shape_data_app/%.cpp
	$(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c -std=c++20 -o$@ $<

$(BUILDDIR_LIB)/libpsql_wrapper.a :  $(BUILDDIR_LIB)/psql_wrapper/psql_wrapper.o
	ar -r -o $($(BUILDDIR_LIB)/psql_wrapper) $@ $^

$(BUILDDIR_LIB)/libtiger_shape_mapper.a :  $(TIGER_SHAPE_PARSER_OBJS)
	ar -r -o $($(BUILDDIR_LIB)/tiger_shape_mapper) $@ $^

$(BUILDDIR_APP)/shape_data_app/shape_data_app: $(BUILDDIR)/app/shape_data_app/shape_data_app.o $(BUILDDIR_LIB)/libpsql_wrapper.a $(BUILDDIR_LIB)/libtiger_shape_mapper.a
	$(LINKXX) -o $@ $(BUILDDIR)/app/shape_data_app/shape_data_app.o -Wl,--start-group -lpsql_wrapper -ltiger_shape_mapper  -lpq -lpthread -lrt -lz -lc -Wl,--end-group
