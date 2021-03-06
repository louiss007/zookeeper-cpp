#include "results.hpp"

#include <ostream>
#include <sstream>
#include <utility>

namespace zk
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities                                                                                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TBuffer>
auto print_buffer(std::ostream& os, const TBuffer& buf)
        -> decltype((os << buf), void())
{
    os << buf;
}

template <typename TBuffer>
void print_buffer(std::ostream& os, const TBuffer& buf, ...)
{
    os << "size=" << buf.size();
}

template <typename TRange>
void print_range(std::ostream& os, const TRange& range)
{
    os << '[';
    bool first = true;
    for (const auto& x : range)
    {
        if (first)
            first = false;
        else
            os << ", ";
        os << x;
    }
    os << ']';
}

template <typename T>
std::string to_string_generic(const T& x)
{
    std::ostringstream os;
    os << x;
    return os.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get_result                                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

get_result::get_result(buffer data, const zk::stat& stat) noexcept :
        _data(std::move(data)),
        _stat(stat)
{ }

get_result::~get_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const get_result& self)
{
    os << "get_result{";
    print_buffer(os, self.data());
    os << ' ' << self.stat();
    return os << '}';
}

std::string to_string(const get_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get_children_result                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

get_children_result::get_children_result(children_list_type children, const stat& parent_stat) noexcept :
        _children(std::move(children)),
        _parent_stat(parent_stat)
{ }

get_children_result::~get_children_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const get_children_result& self)
{
    os << "get_children_result{";
    print_range(os, self.children());
    os << " parent=" << self.parent_stat();
    return os << '}';
}

std::string to_string(const get_children_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exists_result                                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

exists_result::exists_result(const optional<zk::stat>& stat) noexcept :
        _stat(stat)
{ }

exists_result::~exists_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const exists_result& self)
{
    os << "exists_result{";
    if (self)
        os << *self.stat();
    else
        os << "(no)";
    return os << '}';
}

std::string to_string(const exists_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// create_result                                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

create_result::create_result(std::string name) noexcept :
        _name(std::move(name))
{ }

create_result::~create_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const create_result& self)
{
    return os << "create_result{name=" << self.name() << '}';
}

std::string to_string(const create_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set_result                                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

set_result::set_result(const zk::stat& stat) noexcept :
        _stat(stat)
{ }

set_result::~set_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const set_result& self)
{
    return os << "set_result{" << self.stat() << '}';
}

std::string to_string(const set_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get_acl_result                                                                                                     //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

get_acl_result::get_acl_result(zk::acl acl, const zk::stat& stat) noexcept :
        _acl(std::move(acl)),
        _stat(stat)
{ }

get_acl_result::~get_acl_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const get_acl_result& self)
{
    return os << "get_acl_result{" << self.acl() << ' ' << self.stat() << '}';
}

std::string to_string(const get_acl_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// event                                                                                                              //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

event::event(event_type type, zk::state state) noexcept :
        _type(type),
        _state(state)
{ }

std::ostream& operator<<(std::ostream& os, const event& self)
{
    return os << "event{" << self.type() << " | " << self.state() << '}';
}

std::string to_string(const event& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// watch_result                                                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

watch_result::watch_result(get_result initial, future<event> next) noexcept :
        _initial(std::move(initial)),
        _next(std::move(next))
{ }

watch_result::~watch_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const watch_result& self)
{
    return os << "watch_result{initial=" << self.initial() << '}';
}

std::string to_string(const watch_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// watch_children_result                                                                                              //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

watch_children_result::watch_children_result(get_children_result initial, future<event> next) noexcept :
        _initial(std::move(initial)),
        _next(std::move(next))
{ }

watch_children_result::~watch_children_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const watch_children_result& self)
{
    return os << "watch_children_result{initial=" << self.initial() << '}';
}

std::string to_string(const watch_children_result& self)
{
    return to_string_generic(self);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// watch_exists_result                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

watch_exists_result::watch_exists_result(exists_result initial, future<event> next) noexcept :
        _initial(std::move(initial)),
        _next(std::move(next))
{ }

watch_exists_result::~watch_exists_result() noexcept
{ }

std::ostream& operator<<(std::ostream& os, const watch_exists_result& self)
{
    return os << "watch_exists_result{initial=" << self.initial() << '}';
}

std::string to_string(const watch_exists_result& self)
{
    return to_string_generic(self);
}

}
