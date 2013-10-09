namespace obj {
  class vertex2 {
    private:
      float coords[2];

    public:
      vertex2(float c[2]);
      vertex2(float x, float y);

      float * get_coords(void);
  };
}
