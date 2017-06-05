HTML=$(patsubst %.md,%.html,$(wildcard *.md))
all : $(HTML)
%.html : %.md
	@pandoc --toc --ascii --smart -N --css=../../css/pandoc.css  --from=markdown --to=html --output=../../html/fr/$@ $<
	@cp -pr img ../../html/fr
