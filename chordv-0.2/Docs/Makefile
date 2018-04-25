.PHONY: clean
all:
	@mkdir -p html/en html/fr html/img pdf/en pdf/fr pdf/img 
	@cp -pr txt/fr/img html/fr
	@cp -pr txt/en/img html/en
	@cp -pr txt/fr/img pdf/fr
	@cp -pr txt/en/img pdf/en
	@make -C txt
clean:
	@make clean -C txt 
