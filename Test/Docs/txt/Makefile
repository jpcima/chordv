HTML=$(patsubst %.txt,%.html,$(wildcard *.txt))
all : $(HTML)
%.html : %.txt
	asciidoc -o $@ $<
	@mv $@ ../html
