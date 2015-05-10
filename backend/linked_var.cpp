#include "linked_var.h"

/*
 * Global hash map from memory address to list of linked_vars
 * which reference that memory address.
 */
unordered_map<void *, vector<linked_var *>*> linked_var::references;

/*
 * Creates a linked_var object, which represents a linked variable.
 * It takes a pointer to the corresponding C++ variable, and the
 * link expression represented as an ExpressionNode.
 */
linked_var::linked_var(void *var, ExpressionNode *exp) {
	int i;

	// Assign member values
	this->address = var;
	this->expression = *exp;
	this->value = exp->evaluate();
	this->has_aux = false;

	// Put references into dependency tree
	if (exp->dependencies != NULL)
		for (i = 0; i < exp->dependencies->size(); i++)
			references[(*exp->dependencies)[i]]->push_back(this);

	// Set the corresponding C++ variable to the proper value.
	this->update_cpp_var();
}

link_val linked_var::get_value() {
    return this->value;
}

void linked_var::update_cpp_var() {
	switch (this->value.type) {
	case (ltINT):
		*(int *)(this->address) = this->value.value.intval;
		break;
	case (ltINT_PTR): 
		*(int *)(this->address) = *(int *)this->value.value.ptr;
		break;
	case (ltDOUBLE):
		*(double *)(this->address) = this->value.value.doubleval;
		break;
	case (ltDOUBLE_PTR):
		*(double *)(this->address) = *(double *)this->value.value.ptr;
		break;
	case (ltSTR):
		 *(string *)this->address = *(new string(*(this->value.value.strval)));
		break;
	case (ltSTR_PTR):
		*(string *)(this->address) = *(string *)this->value.value.ptr;
		break;
	default:
		break;
	}
}

/*
 * Update the value of a linked variable, and all the linked
 * variables that depend on it, based on the present values  of the
 * relevant C++ variables, at least one of which presumably has
 * changed.
 */
void linked_var::update() {
	int i;
	this->value = this->expression.evaluate();
	this->update_cpp_var();

	if (this->has_aux)
		this->call_aux(&this->value.value);

	// Recursively update children
	if (references[this->address] != NULL)
		for (i = 0; i < references[this->address]->size(); i++)
			if ((*references[this->address])[i] != this)
				(*references[this->address])[i]->update();
}

/*
 * Set the present linked_var to the given value, then accordingly
 * update all linked_vars which depend on this one.
 */
void linked_var::update(link_val new_value) {
	int i;
	this->value = new_value;
	this->update_cpp_var();

	// Recursively update children
	for (i = 0; i < references[this->address]->size(); i++)
		(*references[this->address])[i]->update();
}

/*
 * This function takes a pointer to the C++ variable to be used in a
 * linked_var. (Each linked_var must have one.) It creates an
 * entry for that var in the dependency tree, if one doesn't already
 * exist.
 */
void linked_var::register_cpp_var (void *var) {
	if (references[var] == NULL)
		references[var] = new vector<linked_var*>();
}

/*
 * Call this function immediately after directly updating a nonlinked
 * variable. It will propagate the changes to all vars linked to it,
 * directly or indirectly.
 */
void linked_var::update_nonlinked_var (void *var) {
	int i;
	if (references[var] != NULL) {
		for (i = 0; i < references[var]->size(); i++) {
			(*references[var])[i]->update();
		}
	}
}

/*
 * Unregister all cpp vars. Used for testing.
 */
void linked_var::reset_refs () {
	references.clear();
}

void linked_var::call_aux (void *arg) {
	switch(this->value.type) {
	case (ltINT):
		this->aux.int_fn(*(int *)arg);
		break;
	case (ltINT_PTR):
		this->aux.int_fn(**(int **)arg);
		break;
	case (ltDOUBLE) :
		this->aux.double_fn(*(double *)arg);
		break;
	case (ltDOUBLE_PTR):
		this->aux.double_fn(**(double **)arg);
		break;
	case (ltBOOL) :
		this->aux.bool_fn(*(bool *)arg);
		break;
	case (ltBOOL_PTR):
		this->aux.bool_fn(**(bool **)arg);
		break;
	case (ltSTR) :
		this->aux.str_fn(*(string **)arg);
		break;
	case (ltSTR_PTR) :
		this->aux.str_fn(*(string **)arg);
		break;
	default :
		return;
	}
}

void linked_var::assign_aux_fn (void *fn) {
	this->has_aux = true;

	switch(this->value.type) {
	case (ltINT) :
		this->aux.int_fn = (void (*)(int))fn;
		break;
	case (ltINT_PTR) :
		this->aux.int_fn = (void (*)(int))fn;
		break;
	case (ltDOUBLE) :
		this->aux.double_fn = (void (*)(double))fn;
		break;
	case (ltDOUBLE_PTR) :
		this->aux.double_fn = (void (*)(double))fn;
		break;
	case (ltBOOL) :
		this->aux.bool_fn = (void (*)(bool))fn;
		break;
	case (ltBOOL_PTR) :
		this->aux.bool_fn = (void (*)(bool))fn;
		break;
	case (ltSTR) :
		this->aux.str_fn = (void (*)(string *))fn;
		break;
	case (ltSTR_PTR) :
		this->aux.str_fn = (void (*)(string *))fn;
		break;
	default :
		return;
	}
}
