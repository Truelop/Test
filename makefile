#Compiler and Linker
CC          := gcc

#The Target Binary Program
TARGET      := rover

#The Directories, Source, Includes, Objects and Binary
SRCDIR      := src
TESTDIR     := tests
BUILDDIR    := obj
TARGETDIR   := bin
SRCEXT      := c
TESTEXT     := c
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -DTEST # -fopenmp -Wall -O3 -g -nodefaultlibs -fno-exceptions
LIBS        := -lglut -lGL -lGLU -lcunit -lm
INCLUDESDIR := -Ivendors/freeglut-3.2.1/include -Ivendors/CUnit-2.1-3/include -Iinclude
LIBSDIR     := -Lvendors/CUnit-2.1-3/lib

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
TESTSOURCES := $(shell find $(TESTDIR) -type f -name *.$(TESTEXT))
TESTOBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TESTSOURCES:.$(TESTEXT)=.$(OBJEXT)))

#Run
run: $(TARGET)
	chmod 744 ./${TARGETDIR}/${TARGET}
	./${TARGETDIR}/${TARGET}

#Defauilt Make
all: directories $(TARGET) run

#Remake
remake: cleaner all

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))
-include $(TESTOBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS) $(TESTOBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $(INCLUDESDIR) ${LIBSDIR} $^ $(LIBS)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDESDIR) ${LIBSDIR} -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCLUDESDIR) ${LIBSDIR} -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Compile Test
$(BUILDDIR)/%.$(OBJEXT): $(TESTDIR)/%.$(TESTEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDESDIR) ${LIBSDIR} -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCLUDESDIR) ${LIBSDIR} -MM $(TESTDIR)/$*.$(TESTEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File Targets
.PHONY: all remake clean cleaner directories run
