#include <iostream>
#include <cstdlib>
#include "p2.h"

//
//Functions for the "List" Part
//

int size(list_t list){
    if(list_isEmpty(list)){return 0;} //zero if empty
    else{return 1+size(list_rest(list));} //otherwise, recursion
}

bool memberOf(list_t list, int val){
    if(list_isEmpty(list)){return false;} //list is empty, stop, val is not a member (return false)
    else if(list_first(list)==val){return true;} //val is the first element, reutrn true
    else{return memberOf(list_rest(list),val);} //recursion to find val in the rest of the list
}

int dot(list_t v1, list_t v2){
    if(list_isEmpty(v1)||list_isEmpty(v2)){return 0;} //either v1/v2 empty, stop, return 0
    else{return list_first(v1)*list_first(v2)+dot(list_rest(v1),list_rest(v2));} //recursion to sumproduct pair by pair
}

bool isIncreasing(list_t v){
    if(size(v)<2){return true;} //zero or one element is increasing by definition
    else if(list_first(v)>list_first(list_rest(v))){return false;} //#2 smaller than #1, decreasing!
    else{return isIncreasing(list_rest(v));} //fine, recursion to check if the rest are increasing
}

static list_t reverse_helper(list_t l1, list_t l2){
    if(list_isEmpty(l1)){return l2;} //Done! all elements in stack l1 has been transferred to l2
    else{return reverse_helper(list_rest(l1),list_make(list_first(l1),l2));} //recursion to move elements of l1 to l2. Gradually, top of l1 becomes bottom of l2
}

list_t reverse(list_t list){
    return reverse_helper(list,list_make()); //use an empty list to contain elements coming from list
}

list_t append(list_t first, list_t second){
    //we prefix first to second to get the same result of append second to first
    if(list_isEmpty(first)){return second;} //all elements in first have been prefixed to second
    else if(list_isEmpty(second)){return first;} //no need to prefix
    else{ //prefix the last element in first to the top of second
        list_t reversed_first=reverse(first);
        return append(reverse(list_rest(reversed_first)),list_make(list_first(reversed_first),second)); //recursion move the last element in first to the top in second
    }
}

static bool isArithmetic_helper(list_t v, int diff){
    if(size(v)<2){return true;} //zero or one element left, stop comparation
    else{
        list_t rest_v=list_rest(v);
        int newdiff=list_first(rest_v)-list_first(v);
        if(newdiff!=diff){return false;} //not follwing the common difference, stop
        else{return isArithmetic_helper(rest_v,diff);} //recursion to check the rest part
    }
}

bool isArithmeticSequence(list_t v){
    if(size(v)<2){return true;} //zero or one element is Arithmetic by definition
    else{
        list_t rest_v=list_rest(v);
        int diff=list_first(rest_v)-list_first(v); //find the common difference
        return isArithmetic_helper(rest_v, diff); //check whether the rest follow this common difference
    }
}

list_t filter_odd(list_t list){
    if(list_isEmpty(list)){return list;} //no elements left, stop filtering
    else{
        list_t rest_v=list_rest(list);
        int first_v=list_first(list);
        if(first_v%2!=1){return filter_odd(rest_v);} //not odd, proceed on
        else{return list_make(first_v,filter_odd(rest_v));} //odd, make it and proceed on
    }
}

list_t filter(list_t list, bool (*fn)(int)){
    if(list_isEmpty(list)){return list;} //no elements left, stop filtering
    else{
        list_t rest_v=list_rest(list);
        int first_v=list_first(list);
        if(!fn(first_v)){return filter(rest_v,fn);} //not satisfy the filter condition, proceed on
        else{return list_make(first_v,filter(rest_v,fn));} //satisfy, make it and proceed on
    }
}

static list_t unique_helper(list_t list, list_t unique_elements){
    if(list_isEmpty(list)){return unique_elements;} //no elements left, stop
    else{
        list_t rest_v=list_rest(list);
        int first_v=list_first(list);
        if(memberOf(unique_elements,first_v)){return unique_helper(rest_v,unique_elements);} //proceed to next element
        else{return unique_helper(rest_v,list_make(first_v,unique_elements));} //add this element to unique list
    }
}

list_t unique(list_t list){
    return reverse(unique_helper(list,list_make()));
}

static list_t insert_helper(list_t first, list_t second, unsigned int n, list_t result){
    if(((unsigned int)size(result))<n){ //move the first n elements in first to result
        return insert_helper(list_rest(first),second,n,list_make(list_first(first),result));
    }
    else if(!list_isEmpty(second)){ //move the second list as a whole to result
        return insert_helper(first,list_rest(second),n,list_make(list_first(second),result));
    }
    else if(!list_isEmpty(first)){ //move the rest of first to result
        return insert_helper(list_rest(first),list_make(),n,list_make(list_first(first),result));
    }
    else{ //complete, return result
        return result;
    }
}

list_t insert_list(list_t first, list_t second, unsigned int n){
    if(list_isEmpty(second)){return first;}
    else if(list_isEmpty(first)){return second;}
    else if(n==((unsigned int)size(first))){return append(first,second);}
    else if(n==0){return append(second,first);}
    else{return reverse(insert_helper(first,second,n,list_make()));}
}

static list_t chop_helper(list_t list, unsigned int n, list_t result){
    if(((unsigned int)size(list))<n+1){return result;} //complete, return result
    else{return chop_helper(list_rest(list),n,list_make(list_first(list),result));}
}

list_t chop(list_t list, unsigned int n){
    return reverse(chop_helper(list,n,list_make()));
}


//
//Functions for the "Binaty Tree" Part
//

int tree_sum(tree_t tree){
    if(tree_isEmpty(tree)){return 0;}
    else{return tree_elt(tree)+tree_sum(tree_left(tree))+tree_sum(tree_right(tree));}
}

bool tree_search(tree_t tree, int val){ //Depth-First, Pre-Order(NLR)
    if(tree_isEmpty(tree)){return false;}
    //search node, then left left childern, and finally right children
    else{return ((tree_elt(tree)==val)||(tree_search(tree_left(tree),val))||(tree_search(tree_right(tree),val)));}
}

int depth(tree_t tree){
    if(tree_isEmpty(tree)){return 0;}
    else{
        int lf_dp=depth(tree_left(tree)); //depth of left children
        int rt_dp=depth(tree_right(tree)); //depth of right children
        return 1+((lf_dp>rt_dp)?lf_dp:rt_dp); //parent depth = deepest children +1
    }
}

int tree_max(tree_t tree){
    if(tree_isEmpty(tree)){
        int int_min=(((unsigned int)(-1))>>1)+1;
        return int_min;
    }
    else{
        int nd=tree_elt(tree); //node (N)
        int lm=tree_max(tree_left(tree)); //max of left(L) children
        int rm=tree_max(tree_right(tree)); //max of right(R) children
        int temp=(nd>lm)?nd:lm;
        return (temp>rm)?temp:rm; //return the max of nd,lm,rm
    }
}

list_t traversal(tree_t tree){//Depth-First, In-Order(LNR)
    if(tree_isEmpty(tree)){return list_make();}
    else{
        list_t left_list=traversal(tree_left(tree)); //L
        list_t right_list=traversal(tree_right(tree)); //N
        return append(left_list,list_make(tree_elt(tree),right_list)); //L,N,R
    }
}

static bool Mono_helper(tree_t tree, int sign){
    bool lf_empty=tree_isEmpty(tree_left(tree));
    bool rt_empty=tree_isEmpty(tree_right(tree));
    if(lf_empty&&rt_empty){return true;} //leaf node, end
    else{
        bool rt_mono=(!rt_empty)&&(((tree_elt(tree_right(tree))-tree_elt(tree))*sign)>=0)&&Mono_helper(tree_right(tree),sign+tree_elt(tree_right(tree))-tree_elt(tree));
        bool lf_mono=(!lf_empty)&&(((tree_elt(tree_left(tree))-tree_elt(tree))*sign)>=0)&&Mono_helper(tree_left(tree),sign+tree_elt(tree_left(tree))-tree_elt(tree));
        return (lf_mono||rt_mono);//either left or right children has mono path would be fine
    }
}

bool tree_hasMonotonicPath(tree_t tree){
    if(tree_isEmpty(tree)){return false;} //empth tree has no mono path by definition
    else{return Mono_helper(tree,0);} 
}

bool tree_allPathSumGreater(tree_t tree, int sum){
    if(tree_isEmpty(tree)){return (0>sum);} //leaf node is checked by its empty subtree
    else{
        bool left_PSG=tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree));
        bool right_PSG=tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree));
        if(tree_isEmpty(tree_right(tree))){return left_PSG;} //no right subtree, right children can be ignored
        else if(tree_isEmpty(tree_left(tree))){return right_PSG;} //no left subtree, left children can be ignored
        else{return (left_PSG && right_PSG);} //both left and right subtree should be PathSumGtreater
    }
}

bool covered_by(tree_t A, tree_t B){
    if(tree_isEmpty(A)){return true;}
    else if(tree_isEmpty(B)){return false;}
    else if(tree_elt(A)!=tree_elt(B)){return false;}
    else{return (covered_by(tree_left(A),tree_left(B))&&covered_by(tree_right(A),tree_right(B)));}
}

bool contained_by(tree_t A, tree_t B){
    if(tree_isEmpty(B)){return tree_isEmpty(A);} //empty B can only contain empty A
    else{return (covered_by(A,B)||contained_by(A,tree_left(B))||contained_by(A,tree_right(B)));}
}

tree_t insert_tree(int elt, tree_t tree){
    if(tree_isEmpty(tree)){return tree_make(elt,tree_make(),tree_make());} //add to node
    else if(elt<tree_elt(tree)){return tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)),tree_right(tree));} //add to left subtree
    else{return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt,tree_right(tree)));} //add to right subtree
}
