#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <complex.h>

// 物理常数
#define EPSILON0 8.854187817e-12  // 真空介电常数 (F/m)
#define MU0      1.2566370614e-6  // 真空磁导率 (N/A²)
#define C0       299792458.0      // 真空光速 (m/s)

// 向量结构体
typedef struct {
    double x, y, z;
} Vector3D;

// 复数向量结构体
typedef struct {
    double complex x, y, z;
} ComplexVector3D;

// 电磁场结构体
typedef struct {
    Vector3D E;  // 电场
    Vector3D B;  // 磁场
    Vector3D D;  // 电位移场
    Vector3D H;  // 磁场强度
} EMField;

// 电流密度结构体
typedef struct {
    Vector3D J;  // 电流密度
    double rho;  // 电荷密度
} CurrentDensity;

// Nabla 算子操作
typedef struct {
    Vector3D (*gradient)(double (*f)(double, double, double), double, double, double, double);
    double (*divergence)(Vector3D (*F)(double, double, double), double, double, double, double);
    Vector3D (*curl)(Vector3D (*F)(double, double, double), double, double, double, double);
} NablaOperator;

// 创建向量
Vector3D vector_create(double x, double y, double z) {
    Vector3D v = {x, y, z};
    return v;
}

// 向量加法
Vector3D vector_add(Vector3D a, Vector3D b) {
    return vector_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

// 向量减法
Vector3D vector_sub(Vector3D a, Vector3D b) {
    return vector_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

// 向量点积
double vector_dot(Vector3D a, Vector3D b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 向量叉积
Vector3D vector_cross(Vector3D a, Vector3D b) {
    return vector_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// 向量标量乘法
Vector3D vector_scale(Vector3D v, double scalar) {
    return vector_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

// 向量模长
double vector_magnitude(Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// 向量标准化
Vector3D vector_normalize(Vector3D v) {
    double mag = vector_magnitude(v);
    if (mag == 0.0) return vector_create(0, 0, 0);
    return vector_scale(v, 1.0 / mag);
}

// 打印向量
void vector_print(const char* name, Vector3D v) {
    printf("%s: (%.6f, %.6f, %.6f)\n", name, v.x, v.y, v.z);
}

// 梯度计算 (∇f)
Vector3D gradient(double (*f)(double, double, double), double x, double y, double z, double h) {
    Vector3D grad;
    
    // 中心差分法计算偏导数
    grad.x = (f(x + h, y, z) - f(x - h, y, z)) / (2 * h);
    grad.y = (f(x, y + h, z) - f(x, y - h, z)) / (2 * h);
    grad.z = (f(x, y, z + h) - f(x, y, z - h)) / (2 * h);
    
    return grad;
}

// 散度计算 (∇·F)
double divergence(Vector3D (*F)(double, double, double), double x, double y, double z, double h) {
    Vector3D F_plus, F_minus;
    
    // x方向偏导数
    F_plus = F(x + h, y, z);
    F_minus = F(x - h, y, z);
    double dFx_dx = (F_plus.x - F_minus.x) / (2 * h);
    
    // y方向偏导数
    F_plus = F(x, y + h, z);
    F_minus = F(x, y - h, z);
    double dFy_dy = (F_plus.y - F_minus.y) / (2 * h);
    
    // z方向偏导数
    F_plus = F(x, y, z + h);
    F_minus = F(x, y, z - h);
    double dFz_dz = (F_plus.z - F_minus.z) / (2 * h);
    
    return dFx_dx + dFy_dy + dFz_dz;
}

// 旋度计算 (∇×F)
Vector3D curl(Vector3D (*F)(double, double, double), double x, double y, double z, double h) {
    Vector3D curl_result;
    Vector3D F_val;
    
    // dFz/dy - dFy/dz
    F_val = F(x, y + h, z);
    double dFz_dy = F_val.z;
    F_val = F(x, y - h, z);
    dFz_dy = (dFz_dy - F_val.z) / (2 * h);
    
    F_val = F(x, y, z + h);
    double dFy_dz = F_val.y;
    F_val = F(x, y, z - h);
    dFy_dz = (dFy_dz - F_val.y) / (2 * h);
    
    curl_result.x = dFz_dy - dFy_dz;
    
    // dFx/dz - dFz/dx
    F_val = F(x, y, z + h);
    double dFx_dz = F_val.x;
    F_val = F(x, y, z - h);
    dFx_dz = (dFx_dz - F_val.x) / (2 * h);
    
    F_val = F(x + h, y, z);
    double dFz_dx = F_val.z;
    F_val = F(x - h, y, z);
    dFz_dx = (dFz_dx - F_val.z) / (2 * h);
    
    curl_result.y = dFx_dz - dFz_dx;
    
    // dFy/dx - dFx/dy
    F_val = F(x + h, y, z);
    double dFy_dx = F_val.y;
    F_val = F(x - h, y, z);
    dFy_dx = (dFy_dx - F_val.y) / (2 * h);
    
    F_val = F(x, y + h, z);
    double dFx_dy = F_val.x;
    F_val = F(x, y - h, z);
    dFx_dy = (dFx_dy - F_val.x) / (2 * h);
    
    curl_result.z = dFy_dx - dFx_dy;
    
    return curl_result;
}

// 拉普拉斯算子 (∇²f)
double laplacian(double (*f)(double, double, double), double x, double y, double z, double h) {
    double f_xx = (f(x + h, y, z) - 2 * f(x, y, z) + f(x - h, y, z)) / (h * h);
    double f_yy = (f(x, y + h, z) - 2 * f(x, y, z) + f(x, y - h, z)) / (h * h);
    double f_zz = (f(x, y, z + h) - 2 * f(x, y, z) + f(x, y, z - h)) / (h * h);
    
    return f_xx + f_yy + f_zz;
}

// 麦克斯韦方程组实现
typedef struct {
    // 高斯电场定律: ∇·E = ρ/ε₀
    double (*gauss_electric)(EMField field, CurrentDensity current, double x, double y, double z, double h);
    
    // 高斯磁场定律: ∇·B = 0
    double (*gauss_magnetic)(EMField field, double x, double y, double z, double h);
    
    // 法拉第定律: ∇×E = -∂B/∂t
    Vector3D (*faraday)(EMField field, Vector3D dB_dt, double x, double y, double z, double h);
    
    // 安培-麦克斯韦定律: ∇×B = μ₀J + μ₀ε₀∂E/∂t
    Vector3D (*ampere_maxwell)(EMField field, CurrentDensity current, Vector3D dE_dt, double x, double y, double z, double h);
} MaxwellEquations;

// 高斯电场定律: ∇·E = ρ/ε₀
double gauss_electric_law(EMField field, CurrentDensity current, double x, double y, double z, double h) {
    // 计算电场的散度
    double div_E = divergence(
        [](double x, double y, double z) -> Vector3D {
            // 这里需要实际的电场函数，简化实现
            return vector_create(0, 0, 0);
        }, x, y, z, h);
    
    // 验证方程: ∇·E - ρ/ε₀ = 0
    return div_E - current.rho / EPSILON0;
}

// 高斯磁场定律: ∇·B = 0
double gauss_magnetic_law(EMField field, double x, double y, double z, double h) {
    // 计算磁场的散度
    double div_B = divergence(
        [](double x, double y, double z) -> Vector3D {
            // 这里需要实际的磁场函数，简化实现
            return vector_create(0, 0, 0);
        }, x, y, z, h);
    
    return div_B;  // 应该接近于0
}

// 法拉第定律: ∇×E = -∂B/∂t
Vector3D faradays_law(EMField field, Vector3D dB_dt, double x, double y, double z, double h) {
    // 计算电场的旋度
    Vector3D curl_E = curl(
        [](double x, double y, double z) -> Vector3D {
            // 这里需要实际的电场函数
            return vector_create(0, 0, 0);
        }, x, y, z, h);
    
    // 验证方程: ∇×E + ∂B/∂t = 0
    return vector_add(curl_E, dB_dt);
}

// 安培-麦克斯韦定律: ∇×B = μ₀J + μ₀ε₀∂E/∂t
Vector3D ampere_maxwell_law(EMField field, CurrentDensity current, Vector3D dE_dt, double x, double y, double z, double h) {
    // 计算磁场的旋度
    Vector3D curl_B = curl(
        [](double x, double y, double z) -> Vector3D {
            // 这里需要实际的磁场函数
            return vector_create(0, 0, 0);
        }, x, y, z, h);
    
    // 计算右边项: μ₀J + μ₀ε₀∂E/∂t
    Vector3D right_side = vector_add(
        vector_scale(current.J, MU0),
        vector_scale(dE_dt, MU0 * EPSILON0)
    );
    
    // 验证方程: ∇×B - (μ₀J + μ₀ε₀∂E/∂t) = 0
    return vector_sub(curl_B, right_side);
}

// 波动方程解算器 (从麦克斯韦方程组推导)
Vector3D electromagnetic_wave(double x, double y, double z, double t, 
                             double amplitude, double kx, double ky, double kz, double omega) {
    // 平面波解: E = E₀ * cos(k·r - ωt)
    double phase = kx * x + ky * y + kz * z - omega * t;
    
    // 假设电场沿x方向偏振
    return vector_create(
        amplitude * cos(phase),
        0,
        0
    );
}

// 计算电磁波中的磁场
Vector3D magnetic_field_wave(double x, double y, double z, double t,
                            double amplitude, double kx, double ky, double kz, double omega) {
    // 对于平面波: B = (k × E) / ω
    Vector3D E = electromagnetic_wave(x, y, z, t, amplitude, kx, ky, kz, omega);
    Vector3D k = vector_create(kx, ky, kz);
    
    Vector3D B = vector_scale(vector_cross(k, E), 1.0 / omega);
    return B;
}

// 计算坡印廷向量 (能流密度)
Vector3D poynting_vector(Vector3D E, Vector3D B) {
    // S = (E × B) / μ₀
    return vector_scale(vector_cross(E, B), 1.0 / MU0);
}

// 计算电磁场能量密度
double energy_density(Vector3D E, Vector3D B) {
    // u = (ε₀E² + B²/μ₀) / 2
    double electric_energy = 0.5 * EPSILON0 * vector_dot(E, E);
    double magnetic_energy = 0.5 * vector_dot(B, B) / MU0;
    return electric_energy + magnetic_energy;
}

// 测试函数：点电荷电场
double point_charge_potential(double x, double y, double z) {
    double r = sqrt(x*x + y*y + z*z);
    if (r == 0) return 0;
    return 1.0 / (4 * M_PI * EPSILON0 * r);
}

// 测试函数：均匀电场
Vector3D uniform_electric_field(double x, double y, double z) {
    return vector_create(1.0, 0, 0);  // 沿x方向的均匀电场
}

// 测试函数：偶极子电场
Vector3D dipole_electric_field(double x, double y, double z) {
    double r = sqrt(x*x + y*y + z*z);
    if (r == 0) return vector_create(0, 0, 0);
    
    double r5 = r * r * r * r * r;
    double p_dot_r = 1.0 * x;  // 假设偶极矩沿x方向
    
    double Ex = (3 * x * p_dot_r - x*x) / r5;
    double Ey = (3 * y * p_dot_r) / r5;
    double Ez = (3 * z * p_dot_r) / r5;
    
    return vector_create(Ex, Ey, Ez);
}

// 演示麦克斯韦方程组
void demonstrate_maxwell_equations() {
    printf("=== 麦克斯韦方程组演示 ===\n\n");
    
    double h = 1e-6;  // 数值微分步长
    double x = 1.0, y = 1.0, z = 1.0;  // 测试点
    
    // 初始化Nabla算子
    NablaOperator nabla;
    
    // 测试梯度计算
    printf("1. 梯度计算测试:\n");
    Vector3D grad = gradient(point_charge_potential, x, y, z, h);
    vector_print("点电荷电势梯度", grad);
    
    // 测试散度计算
    printf("\n2. 散度计算测试:\n");
    double div = divergence(uniform_electric_field, x, y, z, h);
    printf("均匀电场散度: %.6f (应为0)\n", div);
    
    // 测试旋度计算
    printf("\n3. 旋度计算测试:\n");
    Vector3D curl_result = curl(uniform_electric_field, x, y, z, h);
    vector_print("均匀电场旋度", curl_result);
    
    // 测试拉普拉斯算子
    printf("\n4. 拉普拉斯算子测试:\n");
    double lap = laplacian(point_charge_potential, x, y, z, h);
    printf("点电荷电势拉普拉斯: %.6f (在r≠0处应为0)\n", lap);
    
    // 电磁波演示
    printf("\n5. 电磁波演示:\n");
    double t = 0;
    double amplitude = 1.0;
    double kx = 2 * M_PI, ky = 0, kz = 0;  // 波矢量
    double omega = C0 * kx;  // 角频率
    
    Vector3D E_wave = electromagnetic_wave(x, y, z, t, amplitude, kx, ky, kz, omega);
    Vector3D B_wave = magnetic_field_wave(x, y, z, t, amplitude, kx, ky, kz, omega);
    
    vector_print("电场 E", E_wave);
    vector_print("磁场 B", B_wave);
    
    // 坡印廷向量
    Vector3D S = poynting_vector(E_wave, B_wave);
    vector_print("坡印廷向量 S", S);
    
    // 能量密度
    double u = energy_density(E_wave, B_wave);
    printf("电磁场能量密度: %.6f J/m³\n", u);
    printf("\n=== 演示完成 ===\n");
}
    // ∇ × E = -iωB
    // ∇ × H = J + iωD
    // ∇ · D = ρ
    // ∇ · B = 0