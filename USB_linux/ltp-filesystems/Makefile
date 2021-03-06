# To cross compile, override one or more of CC, AR, CROSS_CFLAGS,
# LOADLIBES, LDFLAGS, & LIB_DIR and be sure to always build from the top level.
#
# To override them from the make commandline, do something like this:
# $ CROSS_COMPILER=/opt/cegl-1.4/hardhat/devkit/ppc/405/bin/powerpc-linux-
# $ make \
#     CROSS_CFLAGS="-mcpu=403 -D__PPC405__" \
#     CC=${CROSS_COMPILER}gcc \
#     AR=${CROSS_COMPILER}ar \
#     LDFLAGS=-static \
#     LOADLIBES="-lpthread -lc -lresolv -lnss_dns -lnss_files -lm -lc"
#
# Alternately, to override them by editing this file, uncomment the 
# following lines:
#   CROSS_COMPILER=/opt/ppc64/powerpc64-linux/bin/powerpc64-linux-
#   CROSS_CFLAGS= -mpowerpc64
#   CC=$(CROSS_COMPILER)gcc
#   AR=$(CROSS_COMPILER)ar 
#   LDFLAGS=-static 
#   LOADLIBES=-lpthread -lc -lresolv -lnss_dns -lnss_files -lm -lc
#   LIB_DIR=/lib64
#   export CC AR LDFLAGS LOADLIBES LIB_DIR
#
# Note: If you override a variable from the commandline all
# assignments to it in the Makefiles will be ignored. To set it both 
# in the commandline and in the Makefiles use a dummy variable like in
# CFLAGS

NPTL:=$(shell getconf GNU_LIBPTHREAD_VERSION 2>/dev/null| grep NPTL; echo $?)
ifeq ($(NPTL),)
export CFLAGS+= -Wall $(CROSS_CFLAGS)
else
export CFLAGS+= -Wall $(CROSS_CFLAGS) -DUSE_NPTL
endif


all: libltp.a 
	@$(MAKE) -C pan $@
	@$(MAKE) -C testcases $@
	@echo
	@echo "***********************************************"
	@echo "** You now need to do a make install as root **"
	@echo "***********************************************"

install: all
	@$(MAKE) -C testcases install
	@./IDcheck.sh

libltp.a:
	@$(MAKE) -C lib $@

menuconfig:
	@./ltpmenu

clean:
	@$(MAKE) -C lib $@
	@$(MAKE) -C pan $@
	@$(MAKE) -C testcases $@
