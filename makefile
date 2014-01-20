
DIR_TEMPLATE_LIBRARY = src
DIR_INTEGRATION_TESTS = integration-tests
DIR_USE_CASES = use-cases

PROJECT_EULER = project-euler
DIR_PROJECT_EULER = $(DIR_INTEGRATION_TESTS)/$(PROJECT_EULER)

PARSE_STREAM = parse-stream
DIR_PARSE_STREAM = $(DIR_USE_CASES)/$(PARSE_STREAM)



all:	library						\
			$(PROJECT_EULER)	\
			$(PARSE_STREAM)


clean:	library_clean						\
				$(PROJECT_EULER)_clean	\
				$(PARSE_STREAM)_clean


allclean: clean all


library:
	$(MAKE) -j 4 -C src


library_clean:
	-$(MAKE) clean -C src


$(PROJECT_EULER):
	$(MAKE) -j 4 -C $(DIR_PROJECT_EULER)


$(PROJECT_EULER)_clean:
	-$(MAKE) clean -C $(DIR_PROJECT_EULER)


$(PARSE_STREAM):
	$(MAKE) -j 4 -C $(DIR_PARSE_STREAM)


$(PARSE_STREAM)_clean:
	-$(MAKE) clean -C $(DIR_PARSE_STREAM)
