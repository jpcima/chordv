.PHONY: fr en clean
HTML=$(patsubst %.md,%.html,$(wildcard *.md))
all : $(HTML) fr en 
%.html : %.md
	@pandoc --toc --ascii --smart -N --css=../css/pandoc.css  --from=markdown --to=html --output=../html/$@ $<
clean:
	@for i in ../html/*; do rm -rf $$i/* ; done 
	@rm -f ../html/*.html
fr:
	@make -C fr
en: 
	@make -C en
