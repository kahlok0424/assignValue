.PHONY: clean All

All:
	@echo "----------Building project:[ assignValue - Debug ]----------"
	@"$(MAKE)" -f  "assignValue.mk"
clean:
	@echo "----------Cleaning project:[ assignValue - Debug ]----------"
	@"$(MAKE)" -f  "assignValue.mk" clean
