# High level design course
# MSc in Electronics Engineering
# II Quarter - 2019
#
# By:
#    Luis Leon
#    Emmanuel Madrigal
#    Eliecer Mora

SOURCES=$(wildcard *.cpp *.hpp)
MODULE=bresenham
SYNTHESISER=vivado_hls

.PHONY: all clean

all: $(MODULE)

$(MODULE) : $(SOURCES)
	$(SYNTHESISER) $@.tcl

clean:
	rm -rf $(MODULE)_accelerator
	rm vivado_hls.log

