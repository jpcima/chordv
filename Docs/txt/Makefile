HTML=$(patsubst %.md,%.html,$(wildcard *.md))
all : $(HTML) 
%.html : %.md
	pandoc --from=markdown --to=html --output=../html/$@  $<
	
