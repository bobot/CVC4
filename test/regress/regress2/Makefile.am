SUBDIRS = .

BINARY = cvc4
LOG_COMPILER = @srcdir@/../run_regression
AM_LOG_FLAGS = $(RUN_REGRESSION_ARGS) @top_builddir@/src/main/$(BINARY)

if AUTOMAKE_1_11
# old-style (pre-automake 1.12) test harness
TESTS_ENVIRONMENT = \
	$(TESTS_ENVIRONMENT) $(LOG_COMPILER) \
	$(AM_LOG_FLAGS) $(LOG_FLAGS)
endif

MAKEFLAGS = -k

# These are run for all build profiles.
# If a test shouldn't be run in e.g. competition mode,
# put it below in "TESTS +="
TESTS =	bmc-ibm-1.smt \
	bmc-ibm-2.smt \
	bmc-ibm-5.smt \
	bmc-ibm-7.smt \
	friedman_n6_i4.smt \
	hole9.cvc \
	qwh.35.405.shuffled-as.sat03-1651.smt \
	eq_diamond14.smt

EXTRA_DIST = $(TESTS)

#if CVC4_BUILD_PROFILE_COMPETITION
#else
#TESTS += \
#	error.cvc
#endif
#
# and make sure to distribute it
#EXTRA_DIST += \
#	error.cvc

# synonyms for "check" in this directory
.PHONY: regress regress2 test
regress regress2 test: check

# do nothing in this subdir
.PHONY: regress0 regress1 regress3
regress0 regress1 regress3:
