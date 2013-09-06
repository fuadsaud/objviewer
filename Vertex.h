class Vertex {
  private:
    float coords[3];

  public:
    Vertex(float c[3]);
    Vertex(float x, float y, float z);

    float * get_coords(void);
};
