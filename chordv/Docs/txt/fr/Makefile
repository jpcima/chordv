HTML=$(patsubst %.md,%.html,$(wildcard *.md))
PDF=$(patsubst %.md,%.pdf,$(wildcard *.md))
all : $(HTML) $(PDF)
%.html : %.md
	@pandoc --toc --ascii --smart -N --css=../../css/pandoc.css  --from=markdown --to=html --output=../../html/fr/$@ $<
	@cp -pr img ../../html/fr
%.pdf : %.md
	@pandoc -s --template ../../css/my-pandoc-latex-fr.template --latex-engine=xelatex -V fontsize:12pt -V papersize:"a4paper" --toc --toc-depth=3 --output=../../pdf/fr/$@  $<
	@cp -pr img ../../pdf/fr
