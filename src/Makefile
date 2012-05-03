#
# OMNeT++/OMNEST Makefile for Mywork4
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = Mywork4$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = -I. -Idisplay -Ievents -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/CheckForEventsCommand.o \
    $O/Command.o \
    $O/DataCache.o \
    $O/DataCacheSet.o \
    $O/DisableNodeCommand.o \
    $O/EventManager.o \
    $O/ForwardingEntry.o \
    $O/ForwardingEntrySet.o \
    $O/HandleAdvertCommand.o \
    $O/HandleDataCommand.o \
    $O/HandleInterestCommand.o \
    $O/HandleMoveModuleCommand.o \
    $O/HandleNeighborCommand.o \
    $O/HandleReinforcementCommand.o \
    $O/HandleRoleAdvertCommand.o \
    $O/MessageHelper.o \
    $O/NodeStartupCommand.o \
    $O/RoutingAndAggregation.o \
    $O/ScheduledEvent.o \
    $O/SendAdvertCommand.o \
    $O/SendDataCommand.o \
    $O/SendInterestCommand.o \
    $O/SendReinforcementCommand.o \
    $O/SendRoleAdvertCommand.o \
    $O/SetRoleCommand.o \
    $O/SoftMessage.o \
    $O/txc20.o \
    $O/GenericMessage_m.o \
    $O/RoutingMessage_m.o \
    $O/tictoc20_m.o

# Message files
MSGFILES = \
    GenericMessage.msg \
    RoutingMessage.msg \
    tictoc20.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f Mywork4 Mywork4.exe libMywork4.so libMywork4.a libMywork4.dll libMywork4.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f display/*_m.cc display/*_m.h
	-rm -f events/*_m.cc events/*_m.h
	-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc display/*.cc events/*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/CheckForEventsCommand.o: CheckForEventsCommand.cc \
	CheckForEventsCommand.h \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	tictoc20_m.h \
	txc20.h
$O/Command.o: Command.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	tictoc20_m.h \
	txc20.h
$O/DataCache.o: DataCache.cc \
	DataCache.h
$O/DataCacheSet.o: DataCacheSet.cc \
	DataCache.h \
	DataCacheSet.h
$O/DisableNodeCommand.o: DisableNodeCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	DisableNodeCommand.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	tictoc20_m.h \
	txc20.h
$O/EventManager.o: EventManager.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	EventManager.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	RoutingAndAggregation.h \
	ScheduledEvent.h \
	tictoc20_m.h \
	txc20.h
$O/ForwardingEntry.o: ForwardingEntry.cc \
	ForwardingEntry.h
$O/ForwardingEntrySet.o: ForwardingEntrySet.cc \
	ForwardingEntry.h \
	ForwardingEntrySet.h
$O/GenericMessage_m.o: GenericMessage_m.cc \
	GenericMessage_m.h
$O/HandleAdvertCommand.o: HandleAdvertCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleAdvertCommand.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/HandleDataCommand.o: HandleDataCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleDataCommand.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/HandleInterestCommand.o: HandleInterestCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleInterestCommand.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/HandleMoveModuleCommand.o: HandleMoveModuleCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleMoveModuleCommand.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/HandleNeighborCommand.o: HandleNeighborCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleNeighborCommand.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/HandleReinforcementCommand.o: HandleReinforcementCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleReinforcementCommand.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/HandleRoleAdvertCommand.o: HandleRoleAdvertCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleRoleAdvertCommand.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/MessageHelper.o: MessageHelper.cc \
	GenericMessage_m.h \
	MessageHelper.h \
	tictoc20_m.h
$O/NodeStartupCommand.o: NodeStartupCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	NodeStartupCommand.h \
	RoutingAndAggregation.h \
	tictoc20_m.h \
	txc20.h
$O/RoutingAndAggregation.o: RoutingAndAggregation.cc \
	RoutingAndAggregation.h
$O/RoutingMessage_m.o: RoutingMessage_m.cc \
	RoutingMessage_m.h
$O/ScheduledEvent.o: ScheduledEvent.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	ScheduledEvent.h \
	tictoc20_m.h \
	txc20.h
$O/SendAdvertCommand.o: SendAdvertCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SendAdvertCommand.h \
	tictoc20_m.h \
	txc20.h
$O/SendDataCommand.o: SendDataCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SendDataCommand.h \
	tictoc20_m.h \
	txc20.h
$O/SendInterestCommand.o: SendInterestCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SendInterestCommand.h \
	tictoc20_m.h \
	txc20.h
$O/SendReinforcementCommand.o: SendReinforcementCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SendReinforcementCommand.h \
	tictoc20_m.h \
	txc20.h
$O/SendRoleAdvertCommand.o: SendRoleAdvertCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SendRoleAdvertCommand.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/SetRoleCommand.o: SetRoleCommand.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	MessageHelper.h \
	RoutingAndAggregation.h \
	SetRoleCommand.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/SoftMessage.o: SoftMessage.cc \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	RoutingAndAggregation.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h
$O/tictoc20_m.o: tictoc20_m.cc \
	tictoc20_m.h
$O/txc20.o: txc20.cc \
	CheckForEventsCommand.h \
	Command.h \
	DataCache.h \
	DataCacheSet.h \
	DisableNodeCommand.h \
	EventManager.h \
	ForwardingEntry.h \
	ForwardingEntrySet.h \
	GenericMessage_m.h \
	HandleAdvertCommand.h \
	HandleDataCommand.h \
	HandleInterestCommand.h \
	HandleMoveModuleCommand.h \
	HandleNeighborCommand.h \
	HandleReinforcementCommand.h \
	HandleRoleAdvertCommand.h \
	MessageHelper.h \
	NodeStartupCommand.h \
	RoutingAndAggregation.h \
	RoutingMessage_m.h \
	ScheduledEvent.h \
	SendAdvertCommand.h \
	SendDataCommand.h \
	SendInterestCommand.h \
	SendReinforcementCommand.h \
	SendRoleAdvertCommand.h \
	SetRoleCommand.h \
	SoftMessage.h \
	tictoc20_m.h \
	txc20.h

