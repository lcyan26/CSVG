#ifndef COBJ_TYPE_H
#define COBJ_TYPE_H

class CObjTypeMgr {
 private:
  typedef std::map<std::string,uint> NameIdMap;
  typedef std::map<uint,std::string> IdNameMap;

  uint      next_id_;
  NameIdMap name_id_map_;
  IdNameMap id_name_map_;

  friend class CObjType;

 public:
  CObjTypeMgr() :
   next_id_(1), name_id_map_(), id_name_map_() {
  }

 protected:
  uint getNextId() {
    return next_id_++;
  }

  void addObjType(const std::string &name, uint id) {
    name_id_map_[name] = id;
    id_name_map_[id  ] = name;
  }

  const std::string &getIdName(uint id) {
    return id_name_map_[id];
  }

  uint getNameId(const std::string & name) {
    return name_id_map_[name];
  }
};

class CObjType {
 private:
  std::string name_;
  uint        id_;

 public:
  CObjType(CObjTypeMgr &mgr, const std::string &name, uint id=0) :
   name_(name), id_(id) {
    if (id_ == 0) id_ = mgr.getNextId();

    mgr.addObjType(name_, id_);
  }

  uint               getId  () const { return id_  ; }
  const std::string &getName() const { return name_; }
};

#endif
