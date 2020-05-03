main: main.pdf

%.pdf: %.tex
	latexmk -pdf -pdflatex="pdflatex -interactive=nonstopmode" -use-make $<

.PHONY: clean deepclean show
clean:
	latexmk -CA
deepclean:
	-rm -f *~ *.ps *.pdf *.aux *.bbl *.blg *.dvi *.idx *.ilg *.ind *.lof *.log *.lot *.toc
show:
	open $(MAIN)

