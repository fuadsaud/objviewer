namespace obj {
  class vertex {
    private:
      float coords[3];

    public:
      vertex(float c[3]);
      vertex(float x, float y, float z);

      float * get_coords(void);
  };
}
