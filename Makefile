.PHONY: assignment

assignment:
	pandoc --from markdown --standalone --out hw03.pdf hw03.md
