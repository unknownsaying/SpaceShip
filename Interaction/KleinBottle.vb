Imports System.math

Public Class KleinBottle
    Inherits PictureBox
    
    Private kleinBottle As KleinBottle
    Private rotationX, rotationY, rotationZ As Double
    
    Public Sub New()
        Me.kleinBottle = New KleinBottle(2.0, 0.8)
        Me.DoubleBuffered = True
        Me.Size = New Size(600, 600)
        Me.BackColor = Color.Black
    End Sub
    
    Protected Overrides Sub OnPaint(e As PaintEventArgs)
        MyBase.OnPaint(e)
        
        Dim g As Graphics = e.Graphics
        g.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
        
        DrawKleinBottle(g)
    End Sub
    
    Private Sub DrawKleinBottle(g As Graphics)
        Dim centerX As Integer = Me.Width \ 2
        Dim centerY As Integer = Me.Height \ 2
        Dim scale As Double = 25.0
        
        Dim uSteps As Integer = 100
        Dim vSteps As Integer = 50
        
        Dim points(uSteps, vSteps) As PointF
        Dim colors(uSteps, vSteps) As Color
        
        ' 计算所有点
        For i As Integer = 0 To uSteps - 1
            Dim u As Double = (i / uSteps) * 2 * PI
            
            For j As Integer = 0 To vSteps - 1
                Dim v As Double = (j / vSteps) * 2 * PI
                
                ' Coordinate
                Dim point3D As Point3D = kleinBottle.GetCartesianCoordinates1(u, v)
                
                ' rotate
                Dim rotated As Point3D = Rotate3D(point3D, rotationX, rotationY, rotationZ)
                
                ' perojection
                Dim depth As Double = 1.0 / (10.0 + rotated.Z)
                Dim screenX As Integer = CInt(centerX + rotated.X * depth * scale)
                Dim screenY As Integer = CInt(centerY + rotated.Y * depth * scale)
                
                points(i, j) = New PointF(screenX, screenY)
                
                ' color
                Dim red As Integer = CInt((u / (2 * PI)) * 255)
                Dim green As Integer = CInt((v / (2 * PI)) * 255)
                Dim blue As Integer = CInt(128 + 127 * Sin(u + v))
                colors(i, j) = Color.FromArgb(red, green, blue)
            Next
        Next
        
        Dim pen As New Pen(Color.White, 1)
        
        ' u
        For i As Integer = 0 To uSteps - 1
            For j As Integer = 0 To vSteps - 2
                If IsVisible(points(i, j)) AndAlso IsVisible(points(i, j + 1)) Then
                    pen.Color = colors(i, j)
                    g.DrawLine(pen, points(i, j), points(i, j + 1))
                End If
            Next
        Next
        ' v
        For j As Integer = 0 To vSteps - 1
            For i As Integer = 0 To uSteps - 2
                If IsVisible(points(i, j)) AndAlso IsVisible(points((i + 1) Mod uSteps, j)) Then
                    pen.Color = colors(i, j)
                    g.DrawLine(pen, points(i, j), points((i + 1) Mod uSteps, j))
                End If
            Next
        Next
        
        pen.Dispose()
    End Sub
    
    Private Function Rotate3D(point As Point3D, rx As Double, ry As Double, rz As Double) As Point3D
        ' X-axis
        Dim y1 As Double = point.Y * Cos(rx) - point.Z * Sin(rx)
        Dim z1 As Double = point.Y * Sin(rx) + point.Z * Cos(rx)
        ' Y-axis
        Dim x2 As Double = point.X * Cos(ry) + z1 * Sin(ry)
        Dim z2 As Double = -point.X * Sin(ry) + z1 * Cos(ry)
        ' Z-axis
        Dim x3 As Double = x2 * Cos(rz) - y1 * Sin(rz)
        Dim y3 As Double = x2 * Sin(rz) + y1 * Cos(rz)
        
        Return New Point3D(x3, y3, z2)
    End Function
    
    Private Function IsVisible(point As PointF) As Boolean
        Return point.X >= 0 AndAlso point.X <= Me.Width AndAlso
               point.Y >= 0 AndAlso point.Y <= Me.Height
    End Function
    
    Public Sub Rotate(dx As Double, dy As Double, dz As Double)
        rotationX += dx
        rotationY += dy
        rotationZ += dz
        Me.Invalidate()
    End Sub
End Class

Public Class KleinBottleDemo
    Inherits Form
    
    Private renderer As KleinBottleRenderer
    Private timer As Timer
    
    Public Sub New()
        Me.Text = "Klein Bottle"
        Me.Size = New Size(800, 800)
        Me.StartPosition = FormStartPosition.CenterScreen
        
        renderer = New KleinBottleRenderer()
        renderer.Dock = DockStyle.Fill
        Me.Controls.Add(renderer)
        
        timer = New Timer()
        timer.Interval = 50
        AddHandler timer.Tick, AddressOf Timer_Tick
        timer.Start()
        
        AddControlPanel()
    End Sub
    
    Private Sub Timer_Tick(sender As Object, e As EventArgs)
        renderer.Rotate(0.01, 0.02, 0.005)
    End Sub
    
End Class