namespace obj {
    class vertex {
        public:
            const static unsigned int x_pos = 0x01;
            const static unsigned int x_neg = 0x02;
            const static unsigned int y_pos = 0x03;
            const static unsigned int y_neg = 0x04;
            const static unsigned int z_pos = 0x05;
            const static unsigned int z_neg = 0x06;

            vertex(float c[3]);
            vertex(float x, float y, float z);

            obj::vertex * move(int direction, int amount = 1);

            float * get_coords(void);

        private:
            float coords[3];

    };
}
