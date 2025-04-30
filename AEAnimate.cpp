#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Organism.h"
#include "Grass.h"
#include "Cricket.h"

emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    

    // arena width and height
    const int num_h_boxes = 25;
    const int num_w_boxes = 25;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    const int num_crickets = 7;
    const int num_grass_patches = 10;

    emp::web::Canvas canvas{width, height, "canvas"};
    emp::Random random{444};
    OrgWorld world{random};

    public:

    AEAnimator() {
        // shove canvas into the div
        // along with a control button

        // Add a title and description to the document
        //MAKE THIS LESS CRINGE BRO
        doc << "<h1>Crickets vs. Grass: A Brown Bunch's Lunch</h1>";
        doc << "<p>Our little  world is home to a community of brown mole crickets. Their </p>";
        doc << "<p>lives are intertwined with the grass. They munch.</p>";
        doc << "<p>on the green blades for sustenance, and as they do, the grass, in turn, continues to grow.</p>";
        doc << "<p>It's a delicate balance: the crickets need the grass to survive, and the grass, </p>";
        doc << "<p>though eaten, persists. Watch this simple cycle of brown and green unfold.</p>";


        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        for (int i = 0; i < num_crickets; i++) {

            emp::Ptr<Organism> cricket = new Cricket(&random); 
            world.AddOrgAt(cricket, random.GetInt(0, num_w_boxes * num_h_boxes));

        }

        for (int i = 0; i < num_grass_patches; i++) {

            emp::Ptr<Organism> grass_patch = new Grass(&random); 
            world.AddOrgAt(grass_patch, random.GetInt(0, num_w_boxes * num_h_boxes));

        }

        world.Resize(num_h_boxes, num_w_boxes);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        for (int x = 0; x < num_w_boxes; x++){

            for (int y = 0; y < num_h_boxes; y++) {

                canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
            }
        }

    }

    void DoFrame() override {
        
        world.Update();
        canvas.Clear();

        int org_num = 0;

        for (int x = 0; x < num_w_boxes; x++){

            for (int y = 0; y < num_h_boxes; y++) {

                if (world.IsOccupied(org_num)) {

                    std::string type = world.GetOrg(org_num).GetType();

                    if (type == "Grass") {

                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "black");

                    } else if (type == "Cricket") {

                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "brown", "black");

                    }
                    
                } else {

                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }

                org_num++;
            }
        }
    }

};

AEAnimator animator;

int main() {animator.Step();}