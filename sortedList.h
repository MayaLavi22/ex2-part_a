#include <iostream>
#include <stdexcept>
namespace mtm
{
    template<class T>
    class SortedList{

    //node fields 
        typedef class node{
            T data;
            node* next;
            friend class SortedList;
        
        public:
            node(T);//node c'tor
            ~node() = default;
        }*Node;

    //iterator fields
        class const_iterator{
            Node ptr;
            const_iterator(const SortedList<T>* list);
            friend class SortedList<T>;

        public:
            const_iterator(const const_iterator&) = default;
            const_iterator& operator=(const const_iterator&) = default;
            ~const_iterator() = default;
            const_iterator& operator++();
            bool operator==(const const_iterator& iterator) const;
            const T& operator*() const;
        };

    //sorted list fields
        private:
            Node head;
            int size;

        public:
            SortedList();
            ~SortedList();
            SortedList(const SortedList&);
            SortedList& operator=(const SortedList&);
            void insert(const T& element);
            void remove(const const_iterator&);
            int length() const;
            template<class Predict>
            SortedList filter(Predict p);
            template <class Function>
            SortedList apply(Function f);
            
            const_iterator begin();
            const_iterator end();

        };

    /*------------------------------------------NODE-------------------------------------------*/
    template<class T>
    SortedList<T>::node::node(T data):
        data(data), next(NULL)
    {}
    /*------------------------------------------NODE-------------------------------------------*/
    /*---------------------------------------SORTED_LIST----------------------------------------*/
    template<class T>
    SortedList<T>::SortedList():
        head(NULL), size(0)
    {}

    template<class T>
    SortedList<T>::~SortedList(){
        for (int i=0;i<size;i++){
            Node toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }

    template<class T>
    SortedList<T>::SortedList(const SortedList<T>& list):
        size(list.size)
    {
        Node tail1 = NULL;
        Node tail2=list.head;
        for (int i = 0; i < size; i++) {
            Node temp = new node(tail2->data);
            temp->next = NULL;
            if (i == 0) {
                head = temp;
                tail1 = head;
                tail2=tail2->next;
            }
            else {
                tail1->next = temp;
                tail1 = tail1->next;
                tail2=tail2->next;
            }
        }
        tail1->next=NULL;
    }

    template<class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& list)
    {
        if (this == &list){
            return *this;
        }
        size=list.size;
        for (int i=0;i<size;i++){ //deleting old data
            Node toDelete = head;
            head = head->next;
            delete toDelete;
        }
        Node tail1=NULL;
        Node tail2=list.head;
        for (int i = 0; i < size; i++) {
            Node temp = new node(tail2->data);
            temp->next = NULL;
            if (i == 0) {
                head = temp;
                tail1 = temp;
                tail2=tail2->next;
            }
            else {
                tail1->next = temp;
                tail1 = tail1->next;
                tail2 = tail2->next;
            }
        }
        tail1->next=NULL;
        return *this;
    }

    template<class T>
    void SortedList<T>::insert(const T& element)
    {
        Node i=head;
        Node ptr= new node(element);
        //ptr->data=element;
            if(i==NULL){ //its the first node
                head=ptr;
                size++;
                return;
            }
            Node temp=i;
            if(element<i->data){//ptr smaller than head
                ptr->next=i;
                head=ptr;
                size++;
                return;
            }
            i=i->next;
            while(i){
                if(element<i->data){
                    temp->next=ptr;
                    ptr->next=i;
                    size++;
                    return;
                }
                i=i->next;
                temp=temp->next;
            }
        temp->next=ptr; 
        size++;
    }

    template<class T>
    void SortedList<T>::remove(const const_iterator& it)
    {
        if(head==NULL){
            return;
        }
        Node i=head;
        if(it==begin()){ //remove the first
            head=head->next;
            delete i;
            size--;
            return;
        }
        Node ptr=i;
        i=i->next;
        typename SortedList<T>::const_iterator it2= begin();
        ++it2;
        for (; !(it2== end()); ++it2){
            if(it==it2){
                ptr->next=i->next;
                size--;
                delete i;
                return;
            }
            ++it2;
            i=i->next;
            ptr=ptr->next;
        }
    }

    template <class T>
    int SortedList<T>::length() const
    {
        return size;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() 
    {
        return const_iterator(this);
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end()
    {
        typename SortedList<T>::const_iterator it= begin();
        for (int i=0;i<size;i++){
            ++it;
        }
        return it;
    }

    template<class T>
    template<class Predict>
    SortedList<T> SortedList<T>::filter(Predict p)
    {
        SortedList<T> result;
        for (typename SortedList<T>::const_iterator it= begin(); !(it== end()); ++it){
            if(p(*it)){
                result.insert(*it);
            }
        }
        return result;
    }

    template<class T>
    template <class Function>
    SortedList<T> SortedList<T>::apply(Function f)
    {
        SortedList<T> result;
        for (typename SortedList<T>::const_iterator it= begin(); !(it== end()); ++it){
            result.insert(f(*it));
        }
        return result;
    }
    /*---------------------------------------SORTED_LIST----------------------------------------*/
    /*------------------------------------------iterator------------------------------*/
    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T>* list):
        ptr(list->head)
    {}

    template<class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++()
    {
        if(ptr==NULL){
            throw std::out_of_range("");
        }
        ptr=ptr->next;
        return *this;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator& iterator) const
    {
        return ptr==iterator.ptr;
    }


    template<class T>
    const T& SortedList<T>::const_iterator::operator*() const
    {
        return ptr->data;
    }
    /*------------------------------------------iterator------------------------------*/
}

