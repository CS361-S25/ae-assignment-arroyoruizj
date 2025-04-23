#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "Organism.h"
#include "Predator.h"
#include "Prey.h"
#include "World.h"

emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    const int num_h_boxes = 10;
    const int num_w_boxes = 10;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};
    emp::Random random{444};
    OrgWorld world{random};

    public:

        AEAnimator() {

            doc << canvas;
            doc << GetToggleButton("Toggle");
            doc << GetStepButton("Step");

            Organism* predator = new Predator(24.3, 56.2);
            Organism* prey = new Prey(15.7, 53.2);

            world.Inject(*predator);
            world.Inject(*prey);

            world.Resize(num_h_boxes, num_w_boxes);
            world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

            for (int x = 0; x < num_w_boxes; x++) {

                for (int y = 0; y < num_h_boxes; y++) {

                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "blue", "black");

                }
            }
        }

        void DoFrame() override {

            world.Update();
            canvas.Clear();

            int org_num = 0;

            for (int x = 0; x < num_w_boxes; x++) {

                for (int y = 0; y < num_h_boxes; y++) {

                    if (world.IsOccupied(org_num)) {

                        std::string type = world.GetOrg(org_num).GetType();

                        if (type == "Predator") {

                            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "red", "black");

                        }

                        else if (type == "Organism") {

                            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "black");
                        }

                        else {

                            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "pink", "black");
                        }

                        org_num++;

                    }
                }
            }
        }
};

AEAnimator animator;

int main() {

    animator.Step();

}