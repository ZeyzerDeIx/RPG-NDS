#ifndef CIRCULAR_DEQUE_H
#define CIRCULAR_DEQUE_H

	//OUROBOROS OPERATION BEGIN!
	#include <iostream>
	#include <vector>

	template<class T> class CircularDeque
	{
		public:
			CircularDeque(unsigned int size=1);

			T& front();
			T& back();
			void push_front(const T& newElement);
			void push_back(const T&  newElement);
			T& operator[](int index);
			void clear();
			unsigned int size();
		private:
			unsigned int m_front;
			unsigned int m_back;
			std::vector<T> m_tab;
	};

	template<typename T> CircularDeque<T>::CircularDeque(unsigned int size)
	{
		for (unsigned int i = 0; i < size; ++i)
			m_tab.push_back(T());
		m_front = 0;
		m_back = size-1;
	}

	template<typename T> T& CircularDeque<T>::front()
	{
		return m_tab[m_front];
	}

	template<typename T> T& CircularDeque<T>::back()
	{
		return m_tab[m_back];
	}

	template<typename T> void CircularDeque<T>::push_front(const T&  newElement)
	{
		m_front = m_back;
		if(m_back--==0) m_back = m_tab.size()-1;
		m_tab[m_front] = newElement;
	}

	template<typename T> void CircularDeque<T>::push_back(const T&  newElement)
	{
		m_back = m_front;
		if(++m_front==m_tab.size()) m_front = 0;
		m_tab[m_back] = newElement;
	}

	template<typename T> T& CircularDeque<T>::operator[](int index)
	{
		return m_tab[(m_front + index)%m_tab.size()];
	}

	template<typename T> void CircularDeque<T>::clear()
	{
		unsigned int size = m_tab.size();
		m_tab.clear();
		for (unsigned int i = 0; i < size; ++i)
			m_tab.push_back(T());
	}

	template<typename T> unsigned int CircularDeque<T>::size()
	{
		return m_tab.size();
	}


#endif//CIRCULAR_DEQUE_H