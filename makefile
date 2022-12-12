clean: 
	@echo "Cleaning"
	-del /a /f /s /q  "*.exe" "*.pdb" "*.ilk" "*.obj"
	@echo "Done!"

build:
	-cl '1-Purchase-gjc/1.cpp' /Fe:'module/1.exe'
	-cl '2-FactoryStructure-gyx/2.cpp' /Fe:'module/2.exe'
	-cl '3-ProductionProcess-hjh/3.cpp' /Fe:'module/3.exe'
	-cl '4-Assemble-tarq/4.cpp' /Fe:'module/4.exe'
	-cl '5-Examine-lsr/5.cpp' /Fe:'module/5.exe'
	-cl '6-Transport-ysh/6.cpp' /Fe:'module/6.exe'
	-cl '7-Sales-xjx/7.cpp' /Fe:'module/7.exe'
	-cl 'main.cpp' /Fe:'main.exe'
	-del /a /f /s /q "*.obj"