Attribute VB_Name = "Module2"
Sub abc()
    ' Get Inventor application
    Dim invApp As Inventor.Application
    Set invApp = ThisApplication

    ' Get active part document
    Dim partDoc As PartDocument
    Set partDoc = invApp.ActiveDocument

    ' Create 3D sketch
    Dim sketch3D As sketch3D
    Set sketch3D = partDoc.ComponentDefinition.Sketches3D.Add

    ' File path (edit this if needed)
    Dim filePath As String
    filePath = "C:\repo\ScanMatrix\scans\processed\ice_cream_processed.TXT"
    ' Open file
    Dim fileNum As Integer
    fileNum = FreeFile()
    On Error GoTo FileError
    Open filePath For Input As #fileNum

    Dim tg As TransientGeometry
    Set tg = invApp.TransientGeometry
    
    Dim line As String
    Dim x As Double, y As Double, z As Double
    Dim points As ObjectCollection
    Set points = invApp.TransientObjects.CreateObjectCollection
    
    Do While Not EOF(fileNum)
        Line Input #fileNum, line
        line = Trim(line)
    
        If line = "" Then
            ' Empty line signals end of one spline
            If points.Count >= 2 Then
                sketch3D.SketchSplines3D.Add points
                Set points = invApp.TransientObjects.CreateObjectCollection
            End If
        Else
            Dim arr() As String
            If InStr(line, ",") > 0 Then
                arr = Split(line, ",")
            Else
                arr = Split(line)
            End If
            
            If UBound(arr) >= 2 Then
                x = CDbl(Trim(arr(0))) / 10 ' mm to cm
                y = CDbl(Trim(arr(1))) / 10
                z = CDbl(Trim(arr(2))) / 10
                points.Add tg.CreatePoint(x, y, z)
            End If
        End If
    Loop
        
    ' Final spline if file does not end with blank line
    If points.Count >= 2 Then
        sketch3D.SketchSplines3D.Add points
    End If
        
    Close #fileNum
    MsgBox "All 3D splines created successfully."
    Exit Sub
        
FileError:
        MsgBox "Error reading file at: " & filePath
        Close #fileNum

End Sub
