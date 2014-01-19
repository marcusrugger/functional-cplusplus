
DIR_TEMPLATE_LIBRARY = src
DIR_INTEGRATION_TESTS = integration-tests
DIR_PROJECT_EULER = $(DIR_INTEGRATION_TESTS)/project-euler


all:	library				\
			project_euler


clean:	library_clean				\
				project_euler_clean


allclean: clean all


library:
	$(MAKE) -j 4 -C src


library_clean:
	-$(MAKE) clean -C src


project_euler:
	$(MAKE) -j 4 -C $(DIR_PROJECT_EULER)


project_euler_clean:
	-$(MAKE) clean -C $(DIR_PROJECT_EULER)
