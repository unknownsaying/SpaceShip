Public Class MobiusSphereRenderer
    Inherits PictureBox
    
    Private mobius As SphericalMobiusRing
    Private rotationX, rotationY As Double
    
    Public Sub New()
        Me.mobius = New SphericalMobiusRing(2.0, 0.3, 1)
        Me.DoubleBuffered = True
        Me.Size = New Size(512, 512)
    End Sub
    
    Protected Overrides Sub OnPaint(e As PaintEventArgs)
        MyBase.OnPaint(e)
        
        Dim g As Graphics = e.Graphics
        g.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
        g.Clear(Color.Black)
        
        DrawMobiusInSphericalCoords(g)
    End Sub
    
    Private Sub DrawMobiusInSphericalCoords(g As Graphics)
        Dim centerX As Integer = Me.Width \ 2
        Dim centerY As Integer = Me.Height \ 2
        Dim scale As Integer = 64
        
        Dim uSteps As Integer = 128
        Dim vSteps As Integer = 24
        
        For i As Integer = 0 To uSteps - 1
            Dim u As Double = (i / uSteps) * 2 * Math.PI
            
            For j As Integer = 0 To vSteps - 1
                Dim v As Double = (j / vSteps) * 2 - 1
                
                Dim spherical As (r As Double, theta As Double, phi As Double) = 
                    mobius.GetSphericalCoordinates(u, v)
                 
                Dim x3d As Double = spherical.r * Math.Sin(spherical.theta) * Math.Cos(spherical.phi)
                Dim y3d As Double = spherical.r * Math.Sin(spherical.theta) * Math.Sin(spherical.phi)
                Dim z3d As Double = spherical.r * Math.Cos(spherical.theta)
                
                Dim rotated As Point3D = RotatePoint(New Point3D(x3d, y3d, z3d), rotationX, rotationY)
                
                Dim screenX As Integer = CInt(centerX + rotated.X * scale)
                Dim screenY As Integer = CInt(centerY + rotated.Y * scale)
                
                Dim colorValue As Integer = CInt((v + 1) * 127) 
                Using brush As New SolidBrush(Color.FromArgb(255, colorValue, 255 - colorValue, 128))
                    g.FillEllipse(brush, screenX - 2, screenY - 2, 4, 4)
                End Using
            Next
        Next
    End Sub
    
    Private Function RotatePoint(point As Point3D, angleX As Double, angleY As Double) As Point3D
     
        Dim x1 As Double = point.X * Math.Cos(angleY) - point.Z * Math.Sin(angleY)
        Dim z1 As Double = point.X * Math.Sin(angleY) + point.Z * Math.Cos(angleY)
        
     
        Dim y2 As Double = point.Y * Math.Cos(angleX) - z1 * Math.Sin(angleX)
        Dim z2 As Double = point.Y * Math.Sin(angleX) + z1 * Math.Cos(angleX)
        
        Return New Point3D(x1, y2, z2)
    End Function
    
    Public Sub Rotate(deltaX As Double, deltaY As Double)
        rotationX += deltaX
        rotationY += deltaY
        Me.Invalidate()
    End Sub
End Class