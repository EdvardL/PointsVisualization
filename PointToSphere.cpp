#include <PointToSphere.h>
#include <string>

bool PointToSphere::loadFromFile(const std::filesystem::path &path)
{
    std::vector<Point3D> newPoints;
    if ( path.is_relative() && path.filename().extension() == ".csv")
    {
        std::fstream inputfile(path.string());

        if (inputfile.is_open())
        {
            std::string line;
            while (std::getline(inputfile, line))
            {
                std::string number;
                std::vector<float> numbers;
                while (std::getline(std::stringstream(line), number, ';'))
                {
                    numbers.push_back(stof(number));
                }
                if (numbers.size() == 3)
                {
                    newPoints.push_back({numbers[0], numbers[1], numbers[2]});
                }
                else return false;
            }
            inputfile.close();
            points_ = decardToSphere(newPoints);
            radius_ = calculateRadius(newPoints);
            return true;
        }
        else return false;
    }
    else
    {
        std::cerr<<"File not exist or file not csv"<<std::endl;
        return false;
    }
}
bool PointToSphere::loadFromList(const std::span<Point3D> &points)
{
    points_ = decardToSphere(points);
    radius_ = calculateRadius(points);
    return true;
}
void PointToSphere::setAngle(float angle1, float angle2)
{
    angle1_ = angle1;
    angle2_ = angle2;
}
std::vector<Point2D> PointToSphere::getVisiblePoints()
{
    std::vector<Point2D> output;
    for (auto point : points_) 
    {
        // if (fabs(point.th - angle2_) <= 180 && fabs(point.ph - angle1_) <= 180) 
        {
            Point2D newPoint;
            newPoint.x = radius_ * sin(point.th + angle2_ * M_PI / 180) * cos(point.ph + angle1_ * M_PI / 180);
            newPoint.y = radius_ * sin(point.th + angle2_ * M_PI / 180) * sin(point.ph + angle1_ * M_PI / 180);
            output.push_back(newPoint);
        }
    }
    return output;
}
std::vector<PointSphere> PointToSphere::decardToSphere(const std::span<Point3D> &points)
{
    std::vector<PointSphere> sphericalPoints;
    for (const auto& point : points) {
        PointSphere sphericalPoint;
        sphericalPoint.ph = atan(point.y / point.x);
        sphericalPoint.th = atan(sqrt(point.x * point.x + point.y * point.y) / point.z);
        sphericalPoints.push_back(sphericalPoint);
    }
    return sphericalPoints;
}
float PointToSphere::calculateRadius(const std::span<Point3D> &points)
{
    if (!points.empty()) return std::sqrt(std::pow(points[0].x, 2) + std::pow(points[0].y, 2) + std::pow(points[0].z, 2));
    else return -1;
}