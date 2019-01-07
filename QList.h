#ifndef GRAPHALGO_QLIST_H
#define GRAPHALGO_QLIST_H

#ifndef NULL
#define NULL 0
#endif

template<class T>
class QList
{
private:
    typedef struct node
    {
        T item;
        node *next,*prev;
    }node;

    int len;
    node *start,*end;

public:
    QList();
    ~QList();

    void push_back(const T i);
    void push_front(const T i);
    void pop_back();
    void pop_front();
    T front();
    T back();
    int size();
    void clear();
    void clear(unsigned int index);
    T get(unsigned int index);
    T& at(unsigned int index);

    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

    int length();
    int indexOf(T val);
};

template<class T>
QList<T>::QList()
{
    len = 0;
    start = NULL;
    end = NULL;
}

template<class T>
QList<T>::~QList()
{
    clear();
}

template<class T>
void QList<T>::push_front(const T i)
{
    node *tmp = new node;
    tmp->item = i;
    tmp->next = NULL;
    tmp->prev = NULL;

    if(start==NULL)
    {
        start = tmp;
        end = tmp;
    }
    else
    {
        tmp->next = start;
        start->prev = tmp;
        start = tmp;
    }
    len++;
}

template<class T>
void QList<T>::push_back(const T i)
{
    node *tmp = new node;
    tmp->item = i;
    tmp->next = NULL;
    tmp->prev = NULL;

    if(end==NULL)
    {
        start = tmp;
        end = tmp;
    }
    else
    {
        tmp->prev = end;
        end->next = tmp;
        end = tmp;
    }
    len++;
}

template<class T>
void QList<T>::pop_front()
{
    if(start!=NULL)
    {
        node *tmp = start;
        start = start->next;
        if(start!=NULL)
            start->prev = NULL;
        else
            end = NULL;
        delete tmp;
        len--;
    }
}

template<class T>
void QList<T>::pop_back()
{
    if(end!=NULL)
    {
        node *tmp = end;
        end = end->prev;
        if(end!=NULL)
            end->next = NULL;
        else
            start = NULL;
        delete tmp;
        len--;
    }
}

template<class T>
T QList<T>::front()
{
    if(start!=NULL)
        return start->item;
    //TODO: Catch error when list is empty
}

template<class T>
T QList<T>::back()
{
    if(end!=NULL)
        return end->item;
    //TODO: Catch error when list is empty
}

template<class T>
int QList<T>::size()
{
    return this->len;
}

template<class T>
void QList<T>::clear()
{
    node *tmp = start;
    while(start!=NULL)
    {
        tmp = start;
        start = start->next;
        delete tmp;
        len--;
    }
    end = NULL;
}

template<class T>
void QList<T>::clear(unsigned int index)
{
    node *tmp = start;
    for(int i=0;i<=index&&tmp!=NULL;i++)
    {
        if(i==index)
        {
            if(tmp->prev!=NULL)
                tmp->prev->next = tmp->next;
            else
                start = tmp->next;

            if(tmp->next!=NULL)
                tmp->next->prev = tmp->prev;
            else
                end = tmp->prev;

            len--;
            delete tmp;
            break;
        }
        else
            tmp=tmp->next;
    }
}

template<class T>
T QList<T>::get(unsigned int index)
{
    node *tmp = start;
    for(int i=0;i<=index&&tmp!=NULL;i++)
    {
        if(i==index)
            return tmp->item;
        else
            tmp=tmp->next;
    }
    //TODO: Catch error when index is out of range
}

template<class T>
T& QList<T>::at(unsigned int index)
{
    node *tmp = start;
    for(int i=0;i<=index&&tmp!=NULL;i++)
    {
        if(i==index)
            return tmp->item;
        else
            tmp=tmp->next;
    }
    //TODO: Catch error when index is out of range
}

template<class T>
int QList<T>::length()
{
    return this->len;
}

template<class T>
int QList<T>::indexOf(T val)
{
    for(int i=0;i<this->size();i++)
        if(this->at(i) == val)
            return i;
    return -1;
}

template<class T>
T& QList<T>::operator[](unsigned int index)
{
    node *tmp = start;
    for(int i=0;i<=index&&tmp!=NULL;i++)
    {
        if(i==index)
            return tmp->item;
        else
            tmp=tmp->next;
    }
    //TODO: Catch error when index is out of range
}


template<class T>
const T& QList<T>::operator[](unsigned int index) const
{
    node *tmp = start;
    for(int i=0;i<=index&&tmp!=NULL;i++)
    {
        if(i==index)
            return tmp->item;
        else
            tmp=tmp->next;
    }
    //TODO: Catch error when index is out of range
}


#endif //GRAPHALGO_QLIST_H
