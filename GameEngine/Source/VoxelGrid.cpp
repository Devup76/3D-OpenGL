#include "VoxelGrid.h"
#include "Shaders/Include/Shader.h"

const std::vector<glm::mat4> VoxelGrid::matrices;

VoxelGrid::VoxelGrid(int size) : GRID_SIZE(size) {
    grid.resize(GRID_SIZE, std::vector<std::vector<Voxel>>(
        GRID_SIZE, std::vector<Voxel>(GRID_SIZE)
    ));
}

bool VoxelGrid::isExposedFace(int x, int y, int z) const
{
    //std::cout << "Accessing voxel at: (" << x << ", " << y << ", " << z << ")" << std::endl;
    
    if (!isValidIndex(x, y, z, GRID_SIZE)) {
        
        //std::cerr << "ERROR::VOXELGRID::OUT-OF-BOUNDS INDICES: (" << x << ", " << y << ", " << z << ")" << std::endl;
        
        // Handle the error by doing one of those return things
        return true;
    }
    else {

        // Check for boundary voxels
        if (x == 0 || x == GRID_SIZE - 1 || y == 0 || y == GRID_SIZE - 1 || z == 0 || z == GRID_SIZE - 1) {
            //std::cout << "This is a boundary voxel: " << "(" << x << " " << y << " " << z << ")" << std::endl;
            return false;
        }

        // Check the neighbors in all six directions
        bool renderFront = (z == 0 || !grid[x][y][z - 1].exists);
        bool renderBack = (z == GRID_SIZE - 1 || !grid[x][y][z + 1].exists);
        bool renderLeft = (x == 0 || !grid[x - 1][y][z].exists);
        bool renderRight = (x == GRID_SIZE - 1 || !grid[x + 1][y][z].exists);
        bool renderTop = (y == GRID_SIZE - 1 || !grid[x][y + 1][z].exists);
        bool renderBottom = (y == 0 || !grid[x][y - 1][z].exists);

        return renderFront || renderBack || renderLeft || renderRight || renderTop || renderBottom;
    }

}

Voxel& VoxelGrid::getVoxel(int x, int y, int z) {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || z < 0 || z >= GRID_SIZE) {
        throw std::runtime_error("Invalid voxel indices");
    }
    return grid[x][y][z];
}

void VoxelGrid::ec()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}

bool VoxelGrid::isValidIndex(int x, int y, int z, const int gridSize) const {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize && z >= 0 && z < gridSize;
}
