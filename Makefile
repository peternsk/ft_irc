JOIN = echo "````"
help: ## Offer a list of documentation URL links
	@clear
	@echo "Select a command:"
	@echo "  0. JOIN"
	@read url_choice; \
    case $$url_choice in \
        0) CHOICE=$(URL_DOCKER);; \
        *) echo "Invalid choice. Exiting." ; exit 1;; \
    esac; \
    open $$CHOICE
	@clear
	@echo "Opening documentation..."

.PHONY: doc