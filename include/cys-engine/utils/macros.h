#ifndef CYS_ENGINE__UTILS_MACROS_H
#define CYS_ENGINE__UTILS_MACROS_H

/* Usefull macros */

// ############# 1) Class Macros #############

// class setter definition
#define SETTER_DEF(var, type) void set_##var(const type &var);

// class setter declaration
#define SETTER_DECL(classname, var, type) \
void classname::set_##var(const type &var) {\
  _##var = var;\
}

// class getter definition
#define GETTER_DEF(var, type) type get_##var();

// class getter declaration
#define GETTER_DECL(classname, var, type) \
type classname::get_##var() {\
  return _##var; \
}

// both definitions
#define ACCESS_DEF(var, type) SETTER_DEF(var, type) GETTER_DEF(var, type)

// both declarations
#define ACCESS_DECL(classname, var, type) SETTER_DECL(classname, var, type)

// ############# 2) Factory Macro #############

#define FACTORY(classname) classname##Factory

#define FACTORY_DEF(classname) classname *FACTORY(classname)();

#define FACTORY_DECL(classname) \
classname *FACTORY(classname)() {\
  return new classname();\
}


#endif
