#include "Defs.h"

struct arraynode
{
  Item this;
};

/******************************************************************************
 * InitArray
 *
 * Arguments: size - number or elements in the array
 *
 * Returns: Pointer to array of arraynodes
 *
 *****************************************************************************/
Array InitArray(int size)
{
  Array array;
  int i;

  array = (Array) malloc( sizeof(ArrayNode*) * size );
  VerifyMalloc( (Item) array );
  for(i = 0; i < size; i++)
  {
    array[i] = (ArrayNode*) malloc( sizeof(ArrayNode) );
  	VerifyMalloc( array[i] );
  	array[i]->this = NULL;
  }

  return array;
}

/******************************************************************************
 * GetArrayNodeItem
 *
 * Arguments: position - position in the array where we want to get them item from
 *						array - pointer to the array in which we want to get them item from
 *
 * Returns: item we wanted to get
 *
 *****************************************************************************/
Item * GetArrayNodeItem(int position, Array array)
{
  /* Check if position is not empty                                   */
  if(array[position] == NULL)
    return NULL;

  return array[position]->this;
}

/******************************************************************************
 * ModifyArrayNodeItem
 *
 * Arguments: position - position in the array where we want to modify the item
 *            pointer - info we want to insert in this position of the array
 *						array - pointer to the array in which we want to modify them item
 *
 * Returns: -
 *
 *****************************************************************************/
void ModifyArrayNodeItem(int position, Item pointer, Array array)
{
  array[position]->this = pointer;
}
/******************************************************************************
 * DeleteNodeItem
 *
 * Arguments: position - position of the array we want to "delete" from the array
 *						array - pointer to the array in which we want to delete the position
 *
 * Returns: -
 *
 *****************************************************************************/
void DeleteNodeItem(int position, Array array)
{
  free(array[position]->this);
}
