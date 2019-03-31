#include "set.h"
#include <deque>

namespace gfx{

utype set::_id_set_counter_=0;
    
set::set() : id(++_id_set_counter_), name("empty_scene") {}
set::set(const char *nm)  : id(++_id_set_counter_), name(nm) {}
set::set(const std::string& nm) : id(++_id_set_counter_), name(nm) {}

void set::tree() const {
    {
        const set& s = *this;
        std::cout<<"\033[01;34m"<<s.name<<"\033[0m"<<" #"<<s.id<<"  "<<s.subsets.size()<<"("<<s.count_sub_subsets()<<") subsets, "<<s.meshes.size()<<"("<<s.count_sub_meshes()<<") meshes, "<<s.count_sub_vertices()<<" vertices, "<<s.count_sub_triangles()<<" triangles"<<std::endl;
    }
    struct stk_t{
        mesh_vector::const_iterator mt,mte;
        set_vector::const_iterator st,ste;
        stk_t (mesh_vector::const_iterator i,mesh_vector::const_iterator ie,set_vector::const_iterator j,set_vector::const_iterator je) : mt(i),mte(ie),st(j),ste(je) {}
        bool finished() {return mt==mte && st==ste;}
        bool has_mesh() {return mt!=mte;}
    };
    std::deque<stk_t> stk;
    stk.emplace_back(meshes.begin(),meshes.end(),subsets.begin(),subsets.end());
    while(!stk.empty())
    {
        if(stk.back().finished())stk.pop_back();
        else if(stk.back().has_mesh())
        {
            const mesh& m = stk.back().mt->second.operator*();
            stk.back().mt++;
            //print m
            for(int i=0;i<stk.size()-1;i++)std::cout<<(stk[i].finished()?"    ":"│   ");
            std::cout<<(stk.back().finished()?"└── ":"├── ");
            std::cout<<"\033[01;35m"<<m.name<<"\033[0m"<<" #"<<m.id<<"  "<<m.n_vertices<<" vertices, "<<m.n_triangles<<" triangles"<<std::endl;
        }
        else
        {
            const set& s = stk.back().st->second.operator*();
            stk.back().st++;
            //print s
            for(int i=0;i<stk.size()-1;i++)std::cout<<(stk[i].finished()?"    ":"│   ");
            std::cout<<(stk.back().finished()?"└── ":"├── ");
            std::cout<<"\033[01;34m"<<s.name<<"\033[0m"<<" #"<<s.id<<"  "<<s.subsets.size()<<"("<<s.count_sub_subsets()<<") subsets, "<<s.meshes.size()<<"("<<s.count_sub_meshes()<<") meshes, "<<s.count_sub_vertices()<<" vertices, "<<s.count_sub_triangles()<<" triangles"<<std::endl;
            stk.emplace_back(s.meshes.begin(),s.meshes.end(),s.subsets.begin(),s.subsets.end());
        }
    }
}

set::~set() {
    
}

utype set::count_sub_subsets() const {
    utype c=subsets.size();
    for(const std::pair<transformator,set_pointer>& s:subsets)c+=s.second->count_sub_subsets();
    return c;
}
utype set::count_sub_meshes() const {
    utype c=meshes.size();
    for(const std::pair<transformator,set_pointer>& s:subsets)c+=s.second->count_sub_meshes();
    return c;
}
utype set::count_sub_vertices() const {
    utype c=0;
    for(const std::pair<transformator,mesh_pointer>& m:meshes)c+=m.second->n_vertices;
    for(const std::pair<transformator,set_pointer>& s:subsets)c+=s.second->count_sub_vertices();
    return c;
}

utype set::count_sub_triangles() const {
    utype c=0;
    for(const std::pair<transformator,mesh_pointer>& m:meshes)c+=m.second->n_triangles;
    for(const std::pair<transformator,set_pointer>& s:subsets)c+=s.second->count_sub_triangles();
    return c;
}

utype set::max_sub_vertices() const {
    utype c=0;
    for(const std::pair<transformator,mesh_pointer>& m:meshes)c=std::max(c,m.second->n_vertices);
    for(const std::pair<transformator,set_pointer>& s:subsets)c=std::max(c,s.second->max_sub_vertices());
    return c;
}

};
