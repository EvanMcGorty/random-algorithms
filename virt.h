#include<iostream>
#include<memory>
#include<vector>


//alternative to unique_ptr<t>
//guaranties that it is never nullptr.
template<typename t>
class virt
{
public:

    //compatibility with unique_ptrs
    virt(std::unique_ptr<t>&& a)
    {
        data = a;
    }

    //compatibility with unique_ptrs
    std::unique_ptr<t> release() &&
    {
        return data;
    }

    //move construction
    virt(virt<t>&& a) :
        data(a.data)
    { }

    //move assignment
    void operator=(virt<t>&& a)
    {
        data = a.data;
    }

    //like make_unique
    template<typename...ts>
    static virt<t> make(ts&&...args)
    {
        return virt<t>{std::make_unique<t>(std::forward<ts>(args)...)};
    }

    //like implicit upcasting
    template<typename b>
    virt<b> upcast() &&
    {
        static_assert(std::is_base_of<b,t>::value || std::is_same<b,t>::value,"to upcast virt<x>&& to virt<y>, x must derive from y");
        return 
    }
    
    //like trying a dynamic cast
    template<typename d>
    bool can_downcast() const
    {
        static_assert(std::is_base_of<t,d>::value || std::is_same<b,t>::value,"to downcast virt<x>&& to virt<y>, x must derive from y");
        return dynamic_cast<d*>(data.get()) != nullptr;
    }
    
    //like doing a static cast
    template<typename d>
    virt<d> downcast() &&
    {
        static_assert(std::is_base_of<t,d>::value || std::is_same<b,t>::value,"to downcast virt<x>&& to virt<y>, x must derive from y");
        assert(can_downcast<d>());
        return virt<d>{std::unique_ptr<d>{static_cast<d*>(data.release())}};
    }

    //member access
    t& operator*()
    {
        return data.operator*();
    }

    //member access
    t* operator->()
    {
        return data.operator->();
    }


private:

    //wrapped data
    std::unique_ptr<t> data;
};