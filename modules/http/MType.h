#ifndef MTYPE_H
#define MTYPE_H

class MType {
public:
  MType() {  }
  string GetExt() const {
    return ext;
  }
  void SetExt(string ext) {
    this->ext = ext;
  }
  string GetType() const {
    return type;
  }
  void SetType(string type) {
    this->type = type;
  }
  virtual ~MType() {}
private:
    string ext;
    string type;
};

#endif /* MTYPE_H */