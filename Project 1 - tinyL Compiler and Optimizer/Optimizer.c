	/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2017                              *
 *  Author: Ulrich Kremer                    *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"


/*int findRegDep(int reg, Instruction *ptr){
	while(ptr != NULL)
		if((ptr->opcode == ADD && ptr->field3 == reg)
				|| (ptr->opcode == SUB && ptr->field3 == reg)
				|| (ptr->opcode == MUL && ptr->field3 == reg)
				|| (ptr->opcode == DIV && ptr->field3 == reg)){

				ptr->critical = 1;

				ptr = ptr->prev;
				}
	return 0;
}
*/


int searchArray(int *Array, int element)
{
	int i;
	for(i = 0; i <= 5000; i++)
	{
		if(Array[i] == element)
		{
			return 1;
		}
	}
	return 0;
}

void deleteElement(int *Array, int element)
{
	int i;
	for(i = 0; i <= 5000; i++)
	{
		if(Array[i] == element)
		{
			Array[i] = -1;
			return;
		}
	}
	return;
}

int main()
{

	int *reg, *offset;
	reg = malloc(sizeof(int)*5000);
	offset = malloc(sizeof(int)*5000);

	int regNum = 0, offsetNum = 0;

	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	Instruction *instr3 = LastInstruction(head);

	if (!head->next->next)
		{
			printf("Error in Optimizer.c line 77: expects 3 instructions");
			 exit(EXIT_FAILURE);
		}

	head->critical =1;

	while(instr3 != head){
		if(instr3->critical){
			instr3 = instr3->prev;
			continue;
		}
		if(instr3->opcode == OUTPUTAI){
				offset[offsetNum] = instr3->field2;
				offsetNum++;
				instr3->critical = 1;
				instr3 = instr3->prev;
				continue;
				}

		if(instr3->opcode == ADD || instr3->opcode == SUB || instr3->opcode == MUL
				|| instr3->opcode == DIV)
		{
			if(searchArray(reg, instr3->field3)){
				instr3->critical = 1;
				reg[regNum] = instr3->field1;
				regNum++;
				reg[regNum] = instr3->field2;
				regNum++;
			}
		}

		if(instr3->opcode == STOREAI)
		{
			if(searchArray(offset, instr3->field3))
			{
				instr3->critical = 1;
				reg[regNum] = instr3->field1;
				regNum++;
				deleteElement(offset, instr3->field3);
			}
		}

		if(instr3->opcode == LOADAI)
		{
			if(searchArray(reg, instr3->field3))
			{
				instr3->critical = 1;
				offset[offsetNum] = instr3->field2;
				offsetNum++;
			}
		}

		if(instr3->opcode == LOADI)
		{
			if(searchArray(reg, instr3->field2))
			{
				instr3->critical = 1;
				offset[offsetNum] = instr3->field1;
				offsetNum++;
			}
		}

		instr3 = instr3->prev;
	}


	if (head)
		PrintInstructionList(stdout, head);
		free(reg);
		free(offset);
		Instruction *temp;
		while(head != NULL)
		{
			temp = head;
			head = head->next;
			free(temp);
		}

	return EXIT_SUCCESS;
}
