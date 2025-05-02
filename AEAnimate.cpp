#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Organism.h"
#include "Grass.h"
#include "Cricket.h"


emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    
    // Constants for the grid size and rectangle dimensions
    // These are used to define the size of the canvas and the rectangles
    // that represent the organisms in the world
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

    /**
     * @brief Constructor for the AEAnimator class.
     * Initializes the canvas, sets up the world, and starts the organisms.
     */
    AEAnimator() {

        // Add a title and description to the document
        InsertText();

        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        StartOrganisms(num_crickets, "Cricket");
        StartOrganisms(num_grass_patches, "Grass");

        world.Resize(num_h_boxes, num_w_boxes);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        // Setup start grid
        for (int x = 0; x < num_w_boxes; x++){

            for (int y = 0; y < num_h_boxes; y++) {

                canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
            }
        }

    }

    /**
     * @brief Function to insert text into the document.
     */
    void InsertText() {

        doc << "<h1>Crickets vs. Grass: A Brown Bunch's Lunch</h1>";
        doc << "<p>Our little  world is home to a community of brown mole crickets. Their </p>";
        doc << "<p>lives are intertwined with the grass. They munch.</p>";
        doc << "<p>on the green blades for sustenance, and as they do, the grass, in turn, continues to grow.</p>";
        doc << "<p>It's a delicate balance: the crickets need the grass to survive, and the grass, </p>";
        doc << "<p>though eaten, persists. Watch this simple cycle of brown and green unfold.</p>";

    }

    /**
     * @brief Function to start organisms in the world.
     * @param _count The number of organisms to start.
     * @param _type The type of organism to start (e.g., "Grass" or "Cricket").
     */
    void StartOrganisms(int _count, std::string _type) {

        for (int i = 0; i < _count; i++) {

            emp::Ptr<Organism> organism;

            if (_type == "Grass") {
                organism = new Grass(&random);
            } else if (_type == "Cricket") {
                organism = new Cricket(&random);
            }

            world.AddOrgAt(organism, random.GetInt(0, num_w_boxes * num_h_boxes));
        }
    }

    /**
     * @brief Function to draw the organisms on the canvas.
     * @param _type The type of organism to draw (e.g., "Grass" or "Cricket").
     * @param x The x-coordinate of the organism's position.
     * @param y The y-coordinate of the organism's position.
     */
    void Draw(std::string _type, int x, int y) {

        if (_type == "Grass") {
            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "black");

        } else if (_type == "Cricket") {

            canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "brown", "black");
        }
    }

    /**
     * @brief Function to update the canvas and draw the organisms.
     * This function is called every time the animation frame is updated.
     */
    void DoFrame() override {
        
        world.Update();
        canvas.Clear();

        int org_num = 0;

        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {

                    std::string type = world.GetOrg(org_num).GetType();
                    Draw(type, x, y);
                    
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