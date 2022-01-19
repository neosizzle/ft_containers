#ifndef __BST_NODE__H__
#define __BST_NODE__H__

template<class T>
class BstNode
{
	private :
		T _data;

	protected :
		BstNode<T>	*left;
		BstNode<T>	*right;

	public :
		BstNode<T>(T data)
		{
			this.data = data;
		}

		BstNode<T>(BstNode &bstnode)
		{
			this.data = bstnode.data;
		}

		~BstNode(){}

		BstNode<T> &operator = (const BstNode &bstnode)
		{
			this.data = bstnode.data;
		}

		T getData ()
		{
			return this._data;
		}

		T setData ()
		{
			return this._data;
		}

};

#endif  //!__BST_NODE__H__