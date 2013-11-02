#include "mesh.h"

namespace obj {
    class scene {
        public:
            scene(bool ra = true);

            void push_mesh(obj::mesh * mesh);

            void render();

        private:
            void render_axis(float size = 9);

            obj::mesh * mesh;

            bool will_render_axis;
    };
}
