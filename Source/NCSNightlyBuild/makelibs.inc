#
# Link the release library (default target)
#
all: $(RELEASE_TARGET)

$(RELEASE_TARGET): $(RELEASE_OBJ)
	if (test -d $(NCS_LIB_PATH)); then echo; \
		else mkdir -p $(NCS_LIB_PATH); fi
	$(LINK) -s $(LFLAGS) $(RELEASE_OBJ) $(LIBS) $(NCS_LIBS) -o $@
#
# Build the release objects
#
$(RELEASE_OBJ): $(SRC)
	if (test -d $(RELEASE_DIR)); then echo; \
	else mkdir -p $(RELEASE_DIR); \
	fi

	cd $(RELEASE_DIR); for i in $? ; do 			\
		echo $$i; 					\
		case $$i in 					\
		*.c) $(CC) -O3 -c $(SRC_DIR)/$$i $(CFLAGS);; 	\
		*.cpp) $(CXX) -O3 -c $(SRC_DIR)/$$i $(CXXFLAGS);;	\
		*.CPP) $(CXX) -O3 -c $(SRC_DIR)/$$i $(CXXFLAGS);;	\
		*) echo Unknown file type for file $$i;;	\
		esac						\
	done

#
# Link the release PURIFIED library (default target), currently only on solaris.
#
ifeq ($(NCS_PLATFORM), solaris)

purify: $(RELEASE_DEBUG_OBJ)
	if (test -d $(NCS_LIB_PATH)); then echo; \
		else mkdir -p $(NCS_LIB_PATH); fi
	$(LINK) $(LFLAGS) $(RELEASE_DEBUG_OBJ) $(LIBS) $(NCS_LIBS) -o $(RELEASE_TARGET)

endif

#
# Link the release QUANTIFIED library (default target)
#
ifeq ($(NCS_PLATFORM), solaris)

quantify: $(RELEASE_DEBUG_OBJ)
	if (test -d $(NCS_LIB_PATH)); then echo; \
		else mkdir -p $(NCS_LIB_PATH); fi
	$(LINK) $(LFLAGS) $(RELEASE_DEBUG_OBJ) $(LIBS) $(NCS_LIBS) -o $(RELEASE_TARGET)

endif

#
# Build the release PURIFIED objects
#
ifeq ($(NCS_PLATFORM), solaris)

$(RELEASE_DEBUG_OBJ): $(SRC)
	if (test -d $(RELEASE_DEBUG_DIR)); then echo; \
		else mkdir -p $(RELEASE_DEBUG_DIR); fi

	cd $(RELEASE_DEBUG_DIR); for i in $? ; do 		\
		echo $$i; 					\
		case $$i in 					\
		*.c) $(CC) -c $(SRC_DIR)/$$i $(CFLAGS) -O3 -g;; 	\
		*.cpp) $(CXX) -c $(SRC_DIR)/$$i $(CXXFLAGS) -O3 -g;;\
		*) echo Unknown file type for file $$i;;	\
		esac						\
	done
#	cd $(RELEASE_DEBUG_DIR); for i in $?; do \
#		echo $$i; $(CC) -c $(SRC_DIR)/$$i $(CFLAGS) -O3 -g; \
#       done

endif

#
# Link the debug library (debug target)
#
debug: $(DEBUG_OBJ)
	if (test -d $(NCS_LIB_PATH)); then echo; \
		else mkdir -p $(NCS_LIB_PATH); fi
	$(LINK) $(LFLAGS) $(DEBUG_OBJ) $(LIBS) $(NCS_LIBS:%=%d) -o $(DEBUG_TARGET)
#
# Build the debug objects
#
$(DEBUG_OBJ): $(SRC)
	if (test -d $(DEBUG_DIR)); then echo; \
		else mkdir -p $(DEBUG_DIR); fi

	cd $(DEBUG_DIR); for i in $? ; do 			\
		echo $$i; 					\
		case $$i in 					\
		*.c) $(CC) -c $(SRC_DIR)/$$i $(CFLAGS) -g -DDEBUG;;\
		*.cpp) $(CXX) -c $(SRC_DIR)/$$i $(CXXFLAGS) -g -DDEBUG -fno-inline;;\
		*) echo Unknown file type for file $$i;;	\
		esac						\
	done

#
# clean target
#
clean:;rm -f $(RELEASE_OBJ) $(DEBUG_OBJ) $(RELEASE_TARGET) $(DEBUG_TARGET)
