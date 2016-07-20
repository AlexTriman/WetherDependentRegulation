/*
 * menu.h
 *
 * Created: 14.11.2015 21:15:04
 *  Author: notebook
 */ 


#ifndef MENU_H_
#define MENU_H_


struct menuItem
{
	void       *Next;
	void       *Previous;
	void       *Parent;
	void       *Child;
	DisplayOption display_option;
	Parameter   edited_parameter;	
	
};


#define MAKE_MENU(Name, Next, Previous, Parent, Child, display_option, edited_parameter) \
                 extern menuItem Next;\
				 extern menuItem Previous; \
				 extern menuItem Parent; \
				 extern menuItem Child; \
				 menuItem Name = {(void*)&Next, (void*)&Previous, (void*)&Parent, (void*)&Child, display_option, edited_parameter}


// для начала — пустой элемент. Который NULL на рисунке



#define NULL_ENTRY Null_Menu











void Menu_Ini(void);
void Editing (Parameter, char);
void RenewScreen (void);
void keyMenu (ButtonValues);

Parameter GetEditedParameter (void);

#endif /* MENU_H_ */