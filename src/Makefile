# High level design course
# MSc in Electronics Engineering
# II Quarter - 2019
#
# By:
#    Luis Leon
#    Emmanuel Madrigal
#    Eliecer Mora

TOPTARGETS := all clean

SUBDIRS := $(wildcard */.)

$(TOPTARGETS): $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
