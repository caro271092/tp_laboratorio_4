#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

LinkedList* ll_newLinkedList(void){
    LinkedList* this = NULL;
    this = (LinkedList*)malloc(sizeof(this));
    if(this!=NULL){
    	this->pFirstNode=NULL; //pCabecera;
    	this->size = 0;
    }
    return this;
}

int ll_len(LinkedList* this){
    int returnAux = -1;
    if(this!=NULL){
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 */
static Node* getNode(LinkedList* this, int nodeIndex){
    Node* pNode=NULL;
    int lenThis;
    lenThis = ll_len(this);
    int i;
    if(this!=NULL && nodeIndex>=0 && nodeIndex<lenThis){
		pNode=this->pFirstNode;
		for(i=0;i<nodeIndex;i++){
			pNode=pNode->pNextNode;
		}
	}
	return pNode;
}

Node* test_getNode(LinkedList* this, int nodeIndex){
    return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement){
    int returnAux = -1;
    Node* nuevoNodo;
    nuevoNodo = (Node*)malloc(sizeof(nuevoNodo));
    Node* nodoAnterior;
    if(this!=NULL && nuevoNodo!=NULL && nodeIndex>=0 && nodeIndex<=this->size){//si la cabecera ya es null se coloca ahí el nodo creado
    	nuevoNodo->pElement=pElement;//cargo el puntero al elemento recibido
    	if(nodeIndex==0){
    		nuevoNodo->pNextNode = this->pFirstNode;
			this->pFirstNode = nuevoNodo;
			this->size++;
			returnAux=0;
		}else{
			nodoAnterior = getNode(this,nodeIndex-1);//obtengo el anterior
			if(nodoAnterior!=NULL){
			nuevoNodo->pNextNode = nodoAnterior->pNextNode;//el siguiente del nuevo es siguiente q era del anterior
			nodoAnterior->pNextNode = nuevoNodo;//el siguiente del anterior es el nuevo
			this->size++;
			returnAux=0;
			}
		}
	}
	return returnAux;
}

int test_addNode(LinkedList* this, int nodeIndex,void* pElement){
    return addNode(this,nodeIndex,pElement);
}

int ll_add(LinkedList* this, void* pElement){
    int returnAux = -1;
    //llama a addnode
    if(this!=NULL){//no se confirma pElem a null por si eso se quiere
	returnAux = addNode(this, ll_len(this),pElement);//la diferencia con addNode es q agrega al final
    }
    return returnAux;
}

void* ll_get(LinkedList* this, int index){
    void* returnAux = NULL;
    Node* nodoObtenido;
    nodoObtenido = getNode(this, index);
    if(nodoObtenido!=NULL){
    returnAux = nodoObtenido->pElement;//retorno el elemento del nodo
    }
    return returnAux;
}

int ll_set(LinkedList* this, int index,void* pElement){
   int returnAux = -1;
   Node* nodoObtenido;
   nodoObtenido = getNode(this, index);
   if(nodoObtenido!=NULL){
	   nodoObtenido->pElement = pElement;
	   returnAux =0;
   }
   return returnAux;
}

int ll_remove(LinkedList* this,int index){
    int returnAux = -1;
    //free(nodo)
    Node* nodoActual;
    Node* nodoAnterior;
    if(this!=NULL){
    nodoActual = getNode(this,index);
	   if(nodoActual!=NULL){
		   if(index==0){//si es la cabecera
			   this->pFirstNode = nodoActual->pNextNode;//se deja como first al q apuntaba el q se elimina
			   this->size--;
			   free(nodoActual);
			   returnAux=0;
		   }else{
		   nodoAnterior = getNode(this,index-1);
			   if(nodoAnterior!=NULL){
				   nodoAnterior->pNextNode = nodoActual->pNextNode;//se apunta el anterior al siguiente del eliminado
				   this->size--;
				   free(nodoActual);
				   returnAux =0;
			   }
		   }
	  }
    }
    return returnAux;
}

int ll_clear(LinkedList* this){
    int returnAux = -1;
    int lenList;
    lenList = ll_len(this);
    int i;
    if(this!=NULL){
    	for(i=lenList;i>=0;i--){
    		ll_remove(this,i);
    	}
    	returnAux=0;
    }
    return returnAux;
}

int ll_deleteLinkedList(LinkedList* this){
    int returnAux = -1;
    int retornoClear;
    if(this!=NULL){
    	retornoClear = ll_clear(this);//para liberar espacio q ocupan nodos
    	if(retornoClear==0){
    	free(this);//librar espacio q ocupa lista
    	returnAux=0;
    	}
    }
    return returnAux;
}

int ll_indexOf(LinkedList* this, void* pElement){
    int returnAux = -1;
    Node* pNode=NULL;
	int lenThis;
	lenThis = ll_len(this);
	int i;
	if(this!=NULL){
		for(i=0;i<lenThis;i++){
			pNode=getNode(this, i);
			if(pNode->pElement==pElement){
				returnAux = i;
				break;
			}
		}
	}
return returnAux;
}

int ll_isEmpty(LinkedList* this){
    int returnAux = -1;
    if(this!=NULL){
		if(this->size==0){
			returnAux =1;
				}else{
					returnAux =0;
				}
    }
    return returnAux;
}

int ll_push(LinkedList* this, int index, void* pElement){
	int returnAux = -1;
	int len;
	len=ll_len(this);
	int retornoAddNode;
	if(this!=NULL && index>=0 && index<=len){
		retornoAddNode = addNode(this, index, pElement);
		if(retornoAddNode==0){
			returnAux =0;
		}
	}
	return returnAux;
}

void* ll_pop(LinkedList* this,int index){
    void* returnAux = NULL;
    Node* pNode;
    int len;
    len=ll_len(this);
    int retornoRemove;
    if(this!=NULL && index>=0 && index<len){
    	pNode = getNode(this, index);
		if(pNode!=NULL){
			returnAux = pNode->pElement;
			retornoRemove = ll_remove(this, index);
			if(retornoRemove!=0){
				returnAux=NULL;
			}
		}
    }
    return returnAux;
}

int ll_contains(LinkedList* this, void* pElement){
    int returnAux = -1;
    int index;
    if(this!=NULL){
    	returnAux=0;
    	index = ll_indexOf(this, pElement);
	    if(index!=-1){
		   returnAux=1;
	    }
    }
    return returnAux;
}

int ll_containsAll(LinkedList* this,LinkedList* this2){
    int returnAux = -1;
    int i;
    int len2;
    void* elemento;
    len2=ll_len(this2);
    if(this!=NULL && this2!=NULL){
    	returnAux=1;//lo dejo en 1 como si la contuviera
    	for(i=0;i<len2;i++){
		   elemento = ll_get(this2, i);
		   if(elemento!=NULL && (ll_contains(this,elemento))==0){
				   returnAux=0;//lo cambio si un elemento no está
				   break;
		   }
	   }
    }
    return returnAux;
}

LinkedList* ll_subList(LinkedList* this,int from,int to){
    LinkedList* cloneArray = NULL;
	int i;
	void* elemento;
	if(this!=NULL && from>=0 && from<ll_len(this) && to>=from && to<=ll_len(this)){
		cloneArray = ll_newLinkedList();
		if(cloneArray!=NULL){
			for(i=from;i<to; i++){
				elemento = ll_get(this, i);
				if(elemento!=NULL){
					ll_add(cloneArray, elemento);
				}
			}
		}
	}
    return cloneArray;
}

LinkedList* ll_clone(LinkedList* this){
    LinkedList* cloneArray = NULL;
	if(this!=NULL){
	  cloneArray = ll_subList(this, 0, ll_len(this));
	}
    return cloneArray;
}

int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order){//0 des 1 as
    int returnAux = -1;
    void* elemento1;
	void* elemento2;
	int len;
	len=ll_len(this);
	int i;
	int j;
	int retornoPFunc;
    if((this!=NULL && pFunc!=NULL && len>0) && ((order==1)||(order==0))){
		for(i=0;i<len-1;i++){//recorro lista
			elemento1 = ll_get(this, i);
			for(j=i+1;j<len;j++){
				elemento2 = ll_get(this, j);
				retornoPFunc = pFunc(elemento1,elemento2);
					if((retornoPFunc>0 && order==1)||(retornoPFunc<0 && order==0)){//quiere decir q el elemento1 es mayor(o menor en 0) q el 2, entonces los cambio de lugar
					ll_set(this, i, elemento2);//en el 0 queda el más chico(o mas grande) pq menor a mayor//mayor a menor//cuando es necesario swap
					ll_set(this, j, elemento1);
					}
			}
		}
		returnAux = 0;
    }
    return returnAux;
}

LinkedList* ll_filter(LinkedList* this,int (*pFn)(void* element)){
	LinkedList* listaFiltrada = NULL;
	int i;
	int len;
	len = ll_len(this);
	void* elemento;//le voy pasando elementos para adentro de Fn acceder al campo q corresponda y obtener lo q quiera filtrar
	if(this!=NULL && pFn!=NULL && len>0){
	   LinkedList* listaFiltrada = ll_newLinkedList();
	   if(listaFiltrada!=NULL){
			for(i=0;i<len;i++){
				elemento=ll_get(this,i);
				if(pFn(elemento)==1){//la f tiene q devolver 1 si el elem cumple
					ll_add(listaFiltrada,elemento);//agrego el elem a la nueva lista
				}
			}
		}
	}
	return listaFiltrada;
}

int ll_count(LinkedList* this, int (*pFn)(void* element)){
	int acumulador=0;
	int i;
	int len;
	len = ll_len(this);
	void* elemento;//le voy pasando elementos para adentro de Fn acceder al campo q corresponda y obtener lo q quiera contar
	int retornoFn;
	if(this!=NULL && pFn!=NULL && len>0){
		for(i=0;i<len;i++){
			elemento=ll_get(this,i);
			retornoFn=pFn(elemento);
			if(retornoFn!=0){//la f tiene q devolver algo mayor a 0 si hay q acumular, sino 0
				acumulador=acumulador+retornoFn;
			}
		}
	}
	return acumulador;
}

