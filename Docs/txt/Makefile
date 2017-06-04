HTML=$(patsubst %.md,%.html,$(wildcard *.md))
all : $(HTML) fr en
%.html : %.md
	@pandoc --toc --ascii --smart -N --css=../css/pandoc.css  --from=markdown --to=html --output=../html/$@ $<
fr:
	make -C fr
en: 
	make -C en
