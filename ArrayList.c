#include "Defs.h"

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

  array = (Array) malloc( sizeof(Item) * size );
  VerifyMalloc( (Item) array );
  for(i = 0; i < size; i++)
  {
  	array[i] = NULL;
  }

  return array;
}

Item GetArrayNode(int position, Array array)
{
  /* Check if position is not empty                                   */
  if(array[position] == NULL)
  {
    printf("Error: The position %d in the array is NULL", position);
   exit(0);
  };

  return array[position];
}

/******************************************************************************
 * ModifyArrayNode
 *
 * Arguments: position - position in the array where we want to modify the item
 *            pointer - info we want to insert in this position of the array
 *						array - pointer to the array in which we want to modify them item
 *
 * Returns: -
 *
 *****************************************************************************/
void ModifyArrayNode(int position, Item pointer, Array array)
{
  array[position] = pointer;
}
/******************************************************************************
 * DeleteNode
 *
 * Arguments: position - position of the array we want to "delete" from the array
 *						array - pointer to the array in which we want to delete the position
 *
 * Returns: -
 *
 *****************************************************************************/
void DeleteNode(int position, Array array)
{
  free(array[position]);
}
